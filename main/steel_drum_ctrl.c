#include "steel_drum_ctrl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define NOTE_COUNT 1
#define NOTE_DURATION_MS 200

uint32_t gpios[NOTE_COUNT] = {2};

void drum_setup() {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    for (int i = 0; i < NOTE_COUNT; i++) {
        io_conf.pin_bit_mask = (1ULL << gpios[i]);
    }

    gpio_config(&io_conf);

    for (int i = 0; i < NOTE_COUNT; i++) {
        gpio_set_level(i, 0);
    }
}

void drum_play_note(int note) {
    ESP_LOGI("STEEL DRUM CTRL", "playing note %d\n", note);
    gpio_set_level(gpios[note], 1);
    vTaskDelay(pdMS_TO_TICKS(NOTE_DURATION_MS));
    gpio_set_level(gpios[note], 0);
}