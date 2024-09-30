#include <stdio.h>
#include "esp_log.h"
#include "esp_camera.h"
#include "camera.h"
#include "esp_heap_caps.h"  // For memory management functions

// Logging tag
static const char *TAG = "camera";

// Function to initialize the camera
esp_err_t init_camera(void) {
    // Log the available heap memory (internal DRAM) and PSRAM memory before initializing the camera
    ESP_LOGI(TAG, "Free internal heap: %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));  // Internal RAM
    ESP_LOGI(TAG, "Free PSRAM: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));        // PSRAM

    // Camera configuration for ESP32-S3-EYE
    camera_config_t config = {
        .pin_pwdn = -1,               // No power down pin
        .pin_reset = -1,              // Software reset
        .pin_xclk = 15,               // XCLK pin
        .pin_sccb_sda = 4,            // SDA pin for SCCB
        .pin_sccb_scl = 5,            // SCL pin for SCCB
        .pin_d7 = 39,                 // Data line 7
        .pin_d6 = 41,                 // Data line 6
        .pin_d5 = 40,                 // Data line 5
        .pin_d4 = 42,                 // Data line 4
        .pin_d3 = 21,                 // Data line 3
        .pin_d2 = 38,                 // Data line 2
        .pin_d1 = 14,                 // Data line 1
        .pin_d0 = 13,                 // Data line 0
        .pin_vsync = 2,               // VSYNC pin
        .pin_href = 12,               // HREF pin
        .pin_pclk = 1,                // PCLK pin
        .xclk_freq_hz = 20000000,     // XCLK frequency: 20 MHz
        .ledc_timer = LEDC_TIMER_0,   // LEDC timer
        .ledc_channel = LEDC_CHANNEL_0, // LEDC channel
        .pixel_format = PIXFORMAT_JPEG, // Use JPEG to reduce memory usage
        .frame_size = FRAMESIZE_QQVGA,  // Reduce frame size to QQVGA (160x120)
        .jpeg_quality = 12,            // Lower JPEG quality to reduce memory usage
        .fb_count = 1                  // Reduce frame buffer count to 1
    };

    // Initialize the camera
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return err;
    }

    ESP_LOGI(TAG, "Camera initialized successfully");

    // Log the available heap and PSRAM memory after initializing the camera
    ESP_LOGI(TAG, "Free internal heap after init: %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));  // Internal RAM
    ESP_LOGI(TAG, "Free PSRAM after init: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));        // PSRAM

    return ESP_OK;
}

// Function to capture an image
esp_err_t capture_image(void) {
    ESP_LOGI(TAG, "Attempting to capture an image");

    // Capture the image
    camera_fb_t *pic = esp_camera_fb_get();
    if (!pic) {
        ESP_LOGE(TAG, "Failed to capture image");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Image captured successfully! Size: %zu bytes", pic->len);

    // Add code here to process or save the image

    // Return the frame buffer back to the driver
    esp_camera_fb_return(pic);

    return ESP_OK;
}
