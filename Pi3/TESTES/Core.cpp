#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <freertos/task.h>

#define LED_PIN_1 2  // Pino do primeiro LED
#define LED_PIN_2 4  // Pino do segundo LED

// Função para acender e apagar o LED no core 0
void core0_led_control(void *parameter) {
  pinMode(LED_PIN_1, OUTPUT);
  
  while (1) {
    digitalWrite(LED_PIN_1, HIGH);   // Acende o LED
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Espera por 1 segundo
    digitalWrite(LED_PIN_1, LOW);    // Apaga o LED
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Espera por 1 segundo
  }
}

// Função para acender e apagar o LED no core 1
void core1_led_control(void *parameter) {
  pinMode(LED_PIN_2, OUTPUT);
  
  while (1) {
    digitalWrite(LED_PIN_2, HIGH);   // Acende o LED
    vTaskDelay(500 / portTICK_PERIOD_MS);   // Espera por 0,5 segundos
    digitalWrite(LED_PIN_2, LOW);    // Apaga o LED
    vTaskDelay(500 / portTICK_PERIOD_MS);   // Espera por 0,5 segundos
  }
}

void setup() {
  // Iniciar tarefa de controle do LED no core 0
  xTaskCreatePinnedToCore(
    core0_led_control,
    "LED Control Core 0",
    10000,
    NULL,
    1,
    NULL,
    0
  );

  // Iniciar tarefa de controle do LED no core 1
  xTaskCreatePinnedToCore(
    core1_led_control,
    "LED Control Core 1",
    10000,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  // Lógica do loop principal (core 0)
}