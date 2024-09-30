#include <stdio.h>
#include "esp_log.h"
#include "camera.h"
#include "freertos/FreeRTOS.h"   // Add this include for FreeRTOS functions
#include "freertos/task.h"       // Add this include for task-related functions

void app_main(void) {
    ESP_LOGI("app_main", "Initializing camera...");

    esp_err_t ret = init_camera();
    if (ret != ESP_OK) {
        ESP_LOGE("app_main", "Camera initialization failed with error 0x%x", ret);
        return;
    }

    ESP_LOGI("app_main", "Camera initialized successfully");

    ESP_LOGI("app_main", "Capturing image...");
    ret = capture_image();
    if (ret != ESP_OK) {
        ESP_LOGE("app_main", "Image capture failed with error 0x%x", ret);
        return;
    }

    ESP_LOGI("app_main", "Image captured successfully");

    // Keep the program running and delay the task by 1000ms (1 second)
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));  // Add task delay to avoid busy looping
    }
}
