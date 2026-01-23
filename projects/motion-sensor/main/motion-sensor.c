#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define PIR_GPIO GPIO_NUM_23
#define LED_GPIO GPIO_NUM_18

void app_main(void)
{
    // Configure PIR as input
    gpio_config_t pir_conf = {
        .pin_bit_mask = 1ULL << PIR_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&pir_conf);

    // Configure LED as output
    gpio_config_t led_conf = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_conf);

    printf("Waiting for PIR sensor to stabilize...\n");
    vTaskDelay(pdMS_TO_TICKS(60000));

    while (1) {
        int motion = gpio_get_level(PIR_GPIO);

        if (motion) {
            printf("🚶 Motion detected! LED ON\n");
            gpio_set_level(LED_GPIO, 1);   // LED ON
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        else{
            gpio_set_level(LED_GPIO, 0); // Ensure LED is OFF
        }
        
            vTaskDelay(pdMS_TO_TICKS(100)); // check every 100 ms
    }
}
