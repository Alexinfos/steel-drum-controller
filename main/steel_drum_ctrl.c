#include "steel_drum_ctrl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define NOTE_COUNT 8
#define NOTE_DURATION_MS 100

uint32_t gpios[NOTE_COUNT] = {2, 4, 16, 17, 5, 18, 19, 21};

void drum_parse_command(const char* command, uint32_t len) {
    char* cmd = malloc(sizeof(char) * len);
    strcpy(cmd, command);

    char* cmdName = strtok(cmd, " ");

    if (cmdName == NULL) {
        free(cmd);
        return;
    }

    if (strcmp(cmdName, "hello") == 0) {
        ESP_LOGI("STEEL DRUM CTRL", "New client connected!\n");
        free(cmd);
        return;
    }

    if (strcmp(cmdName, "play") == 0) {
        char* noteStr = strtok(NULL, " ");
        if (noteStr == NULL) return;
        
        int noteNumber = atoi(noteStr);
        drum_play_note(noteNumber);

        free(cmd);
        return;
    }

    if (strcmp(cmdName, "play_multiple") == 0) {
        char* noteCountStr = strtok(NULL, " ");
        if (noteCountStr == NULL) {
            free(cmd);
            return;
        }
        
        int noteCount = atoi(noteCountStr);
        if (noteCount >= NOTE_COUNT) {
            noteCount = NOTE_COUNT - 1;
        }
        int notes[NOTE_COUNT] = {};
        for (int i = 0; i < noteCount && i < NOTE_COUNT; i++) {
            char* noteStr = strtok(NULL, " ");
            if (noteStr == NULL) {
                notes[i] = -1;
                continue;
            }
            
            notes[i] = atoi(noteStr);
        }
        drum_play_multiple(notes, noteCount);

        free(cmd);
        return;
    }
    free(cmd);
}

void drum_setup() {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pin_bit_mask = 0;

    for (int i = 0; i < NOTE_COUNT; i++) {
        io_conf.pin_bit_mask |= (1ULL << gpios[i]);
    }

    gpio_config(&io_conf);

    for (int i = 0; i < NOTE_COUNT; i++) {
        gpio_set_level(i, 0);
    }
}

void drum_play_note(int note) {
    if (note < 0 || note >= NOTE_COUNT) {
        ESP_LOGE("STEEL DRUM CTRL", "Unable to play note %d (out of acceptable range)\n", note);
        return;
    }
    ESP_LOGI("STEEL DRUM CTRL", "Playing note %d (pin %ld)\n", note, gpios[note]);
    gpio_set_level(gpios[note], 1);
    vTaskDelay(pdMS_TO_TICKS(NOTE_DURATION_MS));
    gpio_set_level(gpios[note], 0);
}

void drum_play_multiple(int* notes, int noteCount) {
    for (int i = 0; i < noteCount; i++) {
        if (notes[i] < 0 || notes[i] >= NOTE_COUNT) continue;
        ESP_LOGI("STEEL DRUM CTRL", "Playing note %d (pin %ld)\n", notes[i], gpios[notes[i]]);
        gpio_set_level(gpios[notes[i]], 1);
    }
    vTaskDelay(pdMS_TO_TICKS(NOTE_DURATION_MS));
    for (int i = 0; i < noteCount; i++) {
        gpio_set_level(gpios[notes[i]], 0);
    }
}
