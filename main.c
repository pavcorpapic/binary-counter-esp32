#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <esp_system.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_COUNT 4 // Number of LEDs in the binary counter
#define DELAY_MS 500  // Delay between count increments

// Replace these GPIO numbers with the pins you are using for the LEDs
const gpio_num_t led_pins[LED_COUNT] = {
    GPIO_NUM_2, GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_12
};

// Function to display a decimal value in binary on the LEDs
void display_binary(uint32_t value) {
    for (int i = 0; i < LED_COUNT; i++) {
        gpio_set_level(led_pins[i], (value & (1 << i)) ? 1 : 0);
       
    }
}

void app_main() {
    // Configure GPIO pins for the LEDs
    for (int i = 0; i < LED_COUNT; i++) {
        gpio_pad_select_gpio(led_pins[i]);
        gpio_set_direction(led_pins[i], GPIO_MODE_OUTPUT);
    }

    uint32_t count = 0;

    while (1) {
        // Display the current count in binary on the LEDs
        display_binary(count);

        // Increment the count (cycling from 0 to 15)
        count = (count + 1) % 16;

        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}
