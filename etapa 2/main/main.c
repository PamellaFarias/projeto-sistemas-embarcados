#include "servo_tools.h"
#include "esp_log.h"
#include "stdlib.h"

void app_main(void)
{
    ServoConfig servo_1 = {
        .gpio_num = 25,
        .pwm_freq = 50,
        .min_angle = 0,
        .max_angle = 180
    };

    ServoConfig servo_2 = {
        .gpio_num = 26,
        .pwm_freq = 50,
        .min_angle = 0,
        .max_angle = 180
    };

    ServoConfig servo_3 = {
        .gpio_num = 27,
        .pwm_freq = 50,
        .min_angle = 0,
        .max_angle = 180
    };

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

    ret = servo_init(&servo_3);

    while (1)
    {
        ServoAngle angle_1 = rand() % 181;
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

        ServoAngle angle_2 = rand() % 181;
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

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ret = hw_servo_deinit(servo_1.gpio_num);
    if (ret != ESP_OK)
    {
        printf("Falha ao desabilitar o servo 1: %s\n", esp_err_to_name(ret));
    }
    else
    {
        printf("Servo 1 desabilitado com sucesso.\n");
    }

    ret = hw_servo_deinit(servo_2.gpio_num);
    if (ret != ESP_OK)
    {
        printf("Falha ao desabilitar o servo 2: %s\n", esp_err_to_name(ret));
    }
    else
    {
        printf("Servo 2 desabilitado com sucesso.\n");
    }
}
