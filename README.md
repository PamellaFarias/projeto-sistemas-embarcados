| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)



## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
# projeto-embarcados-parte_2
| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# Controle de Servos para ESP32

Este projeto demonstra como controlar servos usando o ESP32 e o driver LEDC (LED Controller) da ESP-IDF. Ele inclui a configuração e o controle de servos através de uma interface de alto nível e uma interface de hardware.


## Índice

1. [Visão Geral](#visão-geral)
2. [Instalação e Configuração](#instalação-e-configuração)
3. [Uso](#uso)
4. [Observações](#observações)
5. [APIs](#apis)

## Visão Geral

Este projeto fornece uma biblioteca para controlar servos motores usando o ESP32. A biblioteca oferece uma interface simples para inicializar servos, definir e obter ângulos, e desinicializar os servos. Utiliza o PWM (Pulse Width Modulation) para controlar a posição dos servos e é baseada no framework ESP-IDF.

## Instalação e Configuração

1. **Clone o Repositório**

   ```bash
   git clone https://github.com/seu-usuario/esp32-servo-control.git
   cd esp32-servo-control

## Estrutura do Projeto

- `servo_hw.h` / `servo_hw.c`: Implementação da interface de hardware para inicialização e controle dos servos.
- `servo_tools.h` / `servo_tools.c`: Interface de alto nível para configuração e controle dos servos.
- `main.c`: Exemplo de aplicação que configura e movimenta dois servos.

## Funcionalidades

- **Inicialização de Servos**: Configuração do GPIO e do canal LEDC para o servo.
- **Configuração do Ângulo**: Definição do ângulo do servo com base na largura do pulso.
- **Desinicialização do Servo**: Liberação do canal LEDC e parada do PWM para o servo.

## Requisitos

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) (framework de desenvolvimento para ESP32)
- [ESP32 Dev Kit](https://www.espressif.com/en/products/devkits)

## Instalação e Configuração

1. **Clone o Repositório**

   ```bash 
   git clone <[url-do-repositorio](https://github.com/GabrielAlbinoo/projeto-embarcados-parte_2.git)>
   cd <diretorio-do-repositorio>
    ```

2. **Configure o Ambiente ESP-IDF**

   Certifique-se de ter o ESP-IDF configurado corretamente.

   ```bash
   export IDF_PATH=/caminho/para/esp-idf
    ```

3. **Construa e Faça o Upload do Firmware**

   Crie e entre no diretório de construção:

   ```bash
   mkdir -p build
   cd build
    ```

   Configure o projeto:

   ```bash
   idf.py set-target esp32
   cd build
    ```
   Compile e faça o upload:

   ```bash
   idf.py build
   idf.py flash
    ```

4. **Monitore a Saída**

   ```bash
   idf.py monitor
    ```

### Diagrama de Blocos
![image](https://github.com/user-attachments/assets/f2d79fc7-746e-4ebb-ba94-d0c0130aea1c)


### Esquemático do Hardware
<img style="width: 80%" src="https://github.com/user-attachments/assets/cad682db-b37a-47ef-9ee1-ebca67dc34c4">

### Máquina de Estados
<img alt="maquina_estado" src="https://github.com/user-attachments/assets/b268fb86-6e7b-4b07-8334-6d19c99886a7">


## Uso

O exemplo `main.c` demonstra como configurar e controlar dois servos conectados aos pinos GPIO 25 e 26 do ESP32. O código movimenta os servos para um ângulo aleatório entre 0 e 180 graus a cada segundo.

### Passos para Usar o Projeto

1. **Inicialização dos Servos**: O código inicializa dois servos com as configurações padrão de ângulo e frequência de PWM. 

2. **Movimentação dos Servos**: A cada segundo, o código gera um ângulo aleatório entre 0 e 180 graus e ajusta a posição dos servos de acordo.

3. **Desinicialização**: Após o loop principal, o código desinicializa os servos e libera os recursos alocados.

### Exemplo de Código

O seguinte trecho de código ilustra como o exemplo `main.c` configura e movimenta os servos:

```c
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

 ```

### Observações

- **Ângulos e Largura do Pulso**: O código assume que os servos estão configurados para aceitar uma largura de pulso entre 500 µs e 2500 µs, correspondendo a ângulos entre 0 e 180 graus. Certifique-se de ajustar esses valores de acordo com as especificações dos seus servos.

- **Delay**: Um atraso de 1 segundo (`vTaskDelay(pdMS_TO_TICKS(1000))`) é usado entre os movimentos dos servos para garantir que eles tenham tempo suficiente para se mover até a nova posição antes de atualizar novamente. Esse intervalo pode ser ajustado conforme necessário para seu aplicativo específico.

- **Configuração do PWM**: O projeto utiliza a frequência PWM de 50 Hz, que é comum para servos padrão. Se estiver usando servos que requerem uma frequência diferente, você precisará ajustar a configuração do timer LEDC no código.

- **Inicialização e Desinicialização**: O código inclui funções para inicializar (`servo_init`) e desinicializar (`hw_servo_deinit`) os servos. Certifique-se de sempre desinicializar os servos quando eles não forem mais necessários para liberar os recursos alocados.

- **Tratamento de Erros**: O código realiza verificações de erro em cada operação crítica. Certifique-se de que a comunicação com o hardware está funcionando corretamente e que não há falhas no hardware.

## APIs

### `hw_servo_init(uint8_t gpio_num)`

Inicializa o servo no GPIO especificado.

**Parâmetros:**

- `gpio_num`: O número do GPIO onde o servo está conectado.

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

### `hw_servo_set_pulse_width(uint8_t gpio_num, uint32_t pulse_width_us)`

Define a largura do pulso PWM para o servo.

**Parâmetros:**

- `gpio_num`: O número do GPIO onde o servo está conectado.
- `pulse_width_us`: Largura do pulso em microssegundos (500 a 2500 µs).

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

### `hw_servo_deinit(uint8_t gpio_num)`

Desinicializa o servo e libera o canal LEDC.

**Parâmetros:**

- `gpio_num`: O número do GPIO onde o servo está conectado.

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

### `servo_init(ServoConfig *config)`

Inicializa o servo com a configuração fornecida.

**Parâmetros:**

- `config`: Estrutura contendo a configuração do servo, incluindo número do GPIO, frequência PWM, e ângulos mínimo e máximo.

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

### `servo_set_angle(ServoConfig *config, ServoAngle angle)`

Define o ângulo do servo.

**Parâmetros:**

- `config`: Estrutura contendo a configuração do servo.
- `angle`: Ângulo a ser definido (entre `min_angle` e `max_angle`).

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

### `servo_get_angle(const ServoConfig *config, ServoAngle *angle)`

Obtém o ângulo atual do servo. (Nota: A funcionalidade de obtenção de ângulo ainda não foi implementada.)

**Parâmetros:**

- `config`: Estrutura contendo a configuração do servo.
- `angle`: Ponteiro para a variável onde o ângulo será armazenado.

**Retorno:**

- `esp_err_t`: Código de erro. `ESP_OK` em caso de sucesso.

# projeto-embarcados-parte_3

| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# Projeto de Controle de Servos com IMU para ESP32

Este projeto utiliza um sensor IMU (Inertial Measurement Unit) para controlar dois servos. Os ângulos de Euler obtidos do sensor são convertidos e usados para definir as posições dos servos.

## Índice

- [Visão Geral](#visão-geral)
- [Estrutura do Código](#estrutura-do-código)
- [Funcionalidades do Projeto](#funcionalidades-do-projeto)
- [Dependências](#dependências)
- [Instalação](#instalação)
- [Uso](#uso)
- [APIs Utilizadas](#apis-utilizadas)

## Visão Geral

Este projeto foi desenvolvido para controlar dois servos utilizando dados de um sensor IMU. O código lê os dados de aceleração e giroscópio, calcula o quaternion e os ângulos de Euler, e mapeia esses ângulos para o intervalo de movimento dos servos.

## Estrutura do Código

O código principal é composto por:

- **Função `map_angle(float angle)`**: Converte um ângulo em radianos para o intervalo de 0 a 180 graus.
- **Função `app_main(void)`**: Função principal que inicializa os servos, lê os dados do sensor IMU e controla os servos com base nos ângulos de Euler.

## Funcionalidades do Projeto

1. **Leitura de Dados do Sensor IMU**:
   - Captura dados de aceleração (em m/s²) e giroscópio (em rad/s) em tempo real.

2. **Cálculo de Quaternion**:
   - Converte os dados do sensor IMU em um quaternion, que representa a orientação do sensor.

3. **Cálculo de Ângulos de Euler**:
   - Deriva os ângulos de Euler (Roll, Pitch e Yaw) a partir do quaternion para facilitar a interpretação da orientação.

4. **Mapeamento de Ângulos**:
   - Mapeia os ângulos de Euler (Roll e Pitch) para um intervalo adequado (0 a 180 graus) para controle dos servos.

5. **Controle de Servos**:
   - Ajusta a posição de dois servos em tempo real com base nos ângulos de Euler, permitindo uma resposta dinâmica aos movimentos detectados.

6. **Saída de Monitoramento**:
   - Exibe dados no terminal, incluindo aceleração, giroscópio, quaternion e ângulos de Euler, para fácil acompanhamento do estado do sistema.

7. **Tratamento de Erros**:
   - Implementa verificação de erros ao inicializar os servos e ao ler os dados do sensor, garantindo robustez no funcionamento.

## Dependências

Este projeto depende das seguintes bibliotecas:

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html) - Framework para desenvolvimento com ESP32.
- Driver I2C - Para comunicação com o sensor IMU.

## Instalação

Para compilar e executar este projeto, siga os passos abaixo:

1. Clone o repositório:
   ```bash
   git clone <[url-do-repositorio](https://github.com/GabrielAlbinoo/projeto-embarcados-parte_3.git)>
   cd <diretorio-do-repositorio>
    ```
2. Instale as dependências necessárias conforme as instruções da [documentação do ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

3. **Configure o Ambiente ESP-IDF**

   Certifique-se de ter o ESP-IDF configurado corretamente.

   ```bash
   export IDF_PATH=/caminho/para/esp-idf
    ```

5. Construa o projeto:
   ```bash
   mkdir -p build
   cd build
    ```
6. Construa e Faça o Upload do Firmware:
   Configure o projeto:

   ```bash
   idf.py set-target esp32
   cd build
    ```
   Compile e faça o upload:

   ```bash
   idf.py build
   idf.py flash
    ```
7. Abra o terminal serial para monitorar a saída:
   ```bash
   idf.py monitor
    ```

### Diagrama de Blocos
![image](https://github.com/user-attachments/assets/7409bb53-8869-42bf-969c-e486cbcaff70)


### Esquemático do Hardware
![Esquematico](https://github.com/GabrielAlbinoo/embarcados-parte-3/blob/master/esquematico.jpeg?raw=true)

### Máquina de Estados
![image](https://github.com/user-attachments/assets/d8c5abe2-8083-4179-9a03-eadd38112d1b)


## Uso
Após a inicialização do sistema, os servos se moverão de acordo com os ângulos de Euler medidos pelo IMU. Certifique-se de que o sensor está corretamente conectado e configurado.

### Passos para Usar o Projeto

Após carregar o firmware no dispositivo ESP32, siga os passos abaixo para utilizar o projeto:

1. **Conexões**: Certifique-se de que o sensor IMU e os servos estão corretamente conectados aos pinos GPIO especificados no código (GPIO 16 e 17 para os servos). Consulte a documentação do seu sensor IMU para as conexões corretas.

2. **Inicialização**: Quando o sistema for ligado, o código inicializará automaticamente os servos e o sensor IMU. O terminal exibirá mensagens informando o status da inicialização.

3. **Leitura de Dados**: O programa começará a ler os dados do sensor IMU continuamente. A cada ciclo, ele calculará os valores de aceleração e giroscópio, além de converter esses dados em um quaternion e, em seguida, em ângulos de Euler.

4. **Movimento dos Servos**: Os ângulos de Euler obtidos (Roll e Pitch) serão mapeados para valores entre 0 e 180 graus. Os servos se moverão conforme os ângulos de Euler, permitindo uma resposta dinâmica aos movimentos detectados pelo sensor.

5. **Monitoramento**: Você poderá visualizar a saída no terminal, que mostrará:
   - Valores de aceleração (em m/s²)
   - Valores de giroscópio (em rad/s)
   - Valores do quaternion
   - Ângulos de Euler (Roll, Pitch, Yaw)
   - Posições dos servos em graus

6. **Interrupção do Programa**: Para interromper a execução do programa, você pode usar o comando de interrupção no terminal (geralmente Ctrl + C).

Certifique-se de que o ambiente está seguro e que os servos não estão obstruídos durante o movimento. Isso garantirá que o sistema funcione corretamente e evite danos ao hardware.

## APIs Utilizadas

Este projeto utiliza várias APIs para interagir com o sensor IMU e controlar os servos. Abaixo estão as principais APIs e suas descrições.

### API do Sensor IMU

- **`imu_read_data(IMUData* data)`**
  - **Descrição**: Lê os dados do sensor IMU e os armazena na estrutura `IMUData`.
  - **Parâmetros**: 
    - `data`: Ponteiro para a estrutura onde os dados serão armazenados.
  - **Retorno**: `ESP_OK` em caso de sucesso, ou um código de erro em caso de falha.

- **`imu_calculate_quaternion(const IMUData* data, Quaternion* quat)`**
  - **Descrição**: Calcula o quaternion a partir dos dados do sensor IMU.
  - **Parâmetros**: 
    - `data`: Ponteiro para a estrutura `IMUData` com os dados do sensor.
    - `quat`: Ponteiro para a estrutura onde o quaternion resultante será armazenado.
  - **Retorno**: `ESP_OK` em caso de sucesso, ou um código de erro em caso de falha.

- **`imu_calculate_euler_angles(const Quaternion* quat, EulerAngle* angles)`**
  - **Descrição**: Converte um quaternion em ângulos de Euler.
  - **Parâmetros**: 
    - `quat`: Ponteiro para a estrutura `Quaternion` contendo os dados do quaternion.
    - `angles`: Ponteiro para a estrutura onde os ângulos de Euler resultantes serão armazenados.
  - **Retorno**: `ESP_OK` em caso de sucesso, ou um código de erro em caso de falha.

### API de Controle de Servos

- **`servo_init(ServoConfig* config)`**
  - **Descrição**: Inicializa um servo com a configuração especificada.
  - **Parâmetros**: 
    - `config`: Ponteiro para a estrutura `ServoConfig` que contém a configuração do servo.
  - **Retorno**: `ESP_OK` em caso de sucesso, ou um código de erro em caso de falha.

- **`servo_set_angle(ServoConfig* config, ServoAngle angle)`**
  - **Descrição**: Define o ângulo de um servo.
  - **Parâmetros**: 
    - `config`: Ponteiro para a estrutura `ServoConfig` do servo.
    - `angle`: O ângulo desejado para o servo.
  - **Retorno**: `ESP_OK` em caso de sucesso, ou um código de erro em caso de falha.

### Estruturas de Dados

- **`IMUData`**
  - **Descrição**: Estrutura que contém os dados lidos do sensor IMU, incluindo aceleração e giroscópio.
  
- **`Quaternion`**
  - **Descrição**: Estrutura que representa a orientação em forma de quaternion.

- **`EulerAngle`**
  - **Descrição**: Estrutura que contém os ângulos de Euler (Roll, Pitch e Yaw).

- **`ServoConfig`**
  - **Descrição**: Estrutura que contém a configuração do servo, incluindo o número do GPIO e o intervalo de ângulos.

Essas APIs permitem a interação eficaz entre o software e o hardware, possibilitando o controle dos servos com base nos dados do sensor IMU.

### Documentação
[Documentação](https://docs.google.com/document/d/1ehZx7MRxHarA1N_aalE3D_Jn-jmAyVCmxsuGigXngUs/edit?usp=sharing)

#### Equipe:

- Álisson Leandro de Souza Silva;

- Amanda Ferreira da Silva Alves;
  
- Ana Carolina Dutra Ramos;
  
- Gabriel Albino de Oliveira;
  
- Pâmella Vitória Gomes Farias;
  
- Sara Aymê Marinho Gaspar.

#### Professor: 

- Alexandre Sales Vasconcelos.

#### Disciplina: 

- Sistemas Embarcados.
