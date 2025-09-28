#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "ESP32S3"
#define DELAY pdMS_TO_TICKS(500)

extern "C" [[noreturn]] void app_main(void) {
    while (true) {
        ESP_LOGI(TAG, "Hello");
        vTaskDelay(DELAY);

        ESP_LOGI(TAG, "World");
        vTaskDelay(DELAY);
    }
}
