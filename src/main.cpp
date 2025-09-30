#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define TAG "ESP32S3"
#define DELAY pdMS_TO_TICKS(2000)

#define BUZZER_GPIO               21
#define BUZZER_TIMER              LEDC_TIMER_0
#define BUZZER_MODE               LEDC_LOW_SPEED_MODE
#define BUZZER_CHANNEL            LEDC_CHANNEL_0
#define BUZZER_DUTY_RES           LEDC_TIMER_13_BIT
#define BUZZER_DUTY               4096
#define BUZZER_FREQUENCY          442

static void buzzer_init() {
    constexpr ledc_timer_config_t BUZZER_timer = {
        .speed_mode       = BUZZER_MODE,
        .duty_resolution  = BUZZER_DUTY_RES,
        .timer_num        = BUZZER_TIMER,
        .freq_hz          = BUZZER_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&BUZZER_timer));

    constexpr ledc_channel_config_t BUZZER_channel = {
        .gpio_num       = BUZZER_GPIO,
        .speed_mode     = BUZZER_MODE,
        .channel        = BUZZER_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = BUZZER_TIMER,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0,
        .sleep_mode     = LEDC_SLEEP_MODE_KEEP_ALIVE,
        .flags          = {0}
    };
    ESP_ERROR_CHECK(ledc_channel_config(&BUZZER_channel));
}

extern "C" [[noreturn]] void app_main(void) {
    buzzer_init();
    while (true) {
        ESP_LOGI(TAG, "Playing sound on GPIO %n...", BUZZER_GPIO);
        vTaskDelay(DELAY);
    }
}
