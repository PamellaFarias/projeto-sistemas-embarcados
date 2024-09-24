#include <stdio.h>
#include "driver/i2c.h"
#include "imu_tools.h"
#include "sensor_imu.h"
#include "servo_tools.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int map_angle(float angle) {
    float degrees = angle * (180.0 / M_PI);

    int mapped_angle = (int)(degrees + 180) / 2;
    
    if (mapped_angle < 0) {
        mapped_angle = 0;
    } else if (mapped_angle > 180) {
        mapped_angle = 180;
    }

    return mapped_angle;
}

void app_main(void)
{
    ServoConfig servo_1 = {
        .gpio_num = 16,
        .pwm_freq = 50,
        .min_angle = 0,
        .max_angle = 180};

    ServoConfig servo_2 = {
        .gpio_num = 17,
        .pwm_freq = 50,
        .min_angle = 0,
        .max_angle = 180};

    esp_err_t ret = servo_init(&servo_1);
    if (ret != ESP_OK)
    {
        printf("Falha ao inicializar o servo 1: %s", esp_err_to_name(ret));
        return;
    }

    ret = servo_init(&servo_2);
    if (ret != ESP_OK)
    {
        printf("Falha ao inicializar o servo 2: %s", esp_err_to_name(ret));
        return;
    }

    esp_err_t resultado;

    while (1)
    {
        printf("===================\n");
        IMUData sensorData;
        resultado = imu_read_data(&sensorData);
        if (resultado == ESP_OK)
        {
            AccelerationData accel_data = sensorData.accel;
            float acell_x = accel_data.x;
            float acell_y = accel_data.y;
            float acell_z = accel_data.z;
            printf("Aceleração (m/s): x = %f, y = %f, z = %f\n", acell_x, acell_y, acell_z);

            GyroscopeData gyro_data = sensorData.gyro;

            float gyro_x_rad_s = gyro_data.x;
            float gyro_y_rad_s = gyro_data.y;
            float gyro_z_rad_s = gyro_data.z ;
            printf("Giroscópio (rad): x = %f, y = %f, z = %f\n", gyro_x_rad_s, gyro_y_rad_s, gyro_z_rad_s);
        }
        else
        {
            printf("Falha ao obter dados do sensor.\n");
        }

        Quaternion quaternion;
        resultado = imu_calculate_quaternion(&sensorData, &quaternion);
        if (resultado == ESP_OK)
        {
            printf("Quaternion: w = %f, x = %f, y = %f, z = %f\n", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        }
        else
        {
            printf("Falha ao calcular o Quaternion.\n");
        }

        EulerAngle euler_angle;
        resultado = imu_calculate_euler_angles(&quaternion, &euler_angle);
        if (resultado == ESP_OK)
        {
            printf("Ângulos de Euler: Roll = %f, Pitch = %f, Yaw = %f\n", euler_angle.roll, euler_angle.pitch, euler_angle.yaw);
        }
        else
        {
            printf("Falha ao calcular os ângulos de Euler.\n");
        }
        printf("*******************\n");
        ServoAngle angle_1 = map_angle(euler_angle.roll);
        ret = servo_set_angle(&servo_1, angle_1);
        if (ret == ESP_OK)
        {
            printf("Servo 1 movido para %d graus.\n", angle_1);
        }
        else
        {
            printf("Falha ao definir o ângulo do servo 1: %s\n", esp_err_to_name(ret));
            break;
        }

        ServoAngle angle_2 = map_angle(euler_angle.pitch);
        ret = servo_set_angle(&servo_2, angle_2);
        if (ret == ESP_OK)
        {
            printf("Servo 2 movido para %d graus.\n", angle_2);
        }
        else
        {
            printf("Falha ao definir o ângulo do servo 2: %s\n", esp_err_to_name(ret));
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
