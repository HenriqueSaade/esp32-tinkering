#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "dht.h"

#define DHT_GPIO_PIN GPIO_NUM_23
#define DHT_TYPE DHT_TYPE_AM2301


void dht_task(void *pvParameters)
{

    float humidity = 0.0;
    float temperature = 0.0;

    while (1)
    {
        if (dht_read_float_data(DHT_TYPE, DHT_GPIO_PIN, &humidity, &temperature) == ESP_OK)
        {
            printf("DHT11 on GPIO %d: Temperature: %.1f°C, Humidity: %.1f%%\n", DHT_GPIO_PIN, temperature, humidity);
        }
        else
        {
            printf("Failed to read from DHT11 on GPIO %d\n", DHT_GPIO_PIN);
        }
        vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 2 seconds
    }
}

void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(5000));
    xTaskCreate(dht_task, "dht_task", 4096, NULL, 5, NULL);
}
