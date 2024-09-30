#ifndef CAMERA_H
#define CAMERA_H

#include "esp_err.h"

// Function to initialize the camera
esp_err_t init_camera(void);

// Function to capture the image
esp_err_t capture_image(void);

#endif // CAMERA_H
