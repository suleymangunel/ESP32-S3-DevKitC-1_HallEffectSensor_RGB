#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/rmt_tx.h"
#include "led_strip_encoder.h"
#include "esp_random.h"

#define LED_GPIO             38                 // Built-in RGB LED (WS2812) pin
#define INPUT_GPIO           4                  // GPIO #4: Hall effect sensor pin (3144)
#define RMT_RES_HZ           (10 * 1000 * 1000) // 10 MHz
#define LED_COUNT            1

void app_main(void)
{
    // --- INPUT pin settings
    gpio_config_t in_cfg = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << INPUT_GPIO,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&in_cfg));

    // --- RMT TX channel and WS2812 encoder
    rmt_channel_handle_t rmt_chan = NULL;
    rmt_tx_channel_config_t tx_cfg = {
        .gpio_num = LED_GPIO,
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = RMT_RES_HZ,
        .mem_block_symbols = 64,
        .trans_queue_depth = 4,
        .flags = { .with_dma = false },
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_cfg, &rmt_chan));

    rmt_encoder_handle_t led_encoder = NULL;
    led_strip_encoder_config_t enc_cfg = { .resolution = RMT_RES_HZ };
    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&enc_cfg, &led_encoder));

    ESP_ERROR_CHECK(rmt_enable(rmt_chan));

    // WS2812: GRB order
    uint8_t grb[3 * LED_COUNT] = {0};
    rmt_transmit_config_t tx_conf = { .loop_count = 0 };

    while (1) {
        int level = gpio_get_level(INPUT_GPIO); //Read Hall Effect Sensor (0:magnetized, 1:demagnetized)

        if (!level) {
            // Input 1: RGB LED will turn RED
            grb[0] = 16;
            grb[1] = 0;
            grb[2] = 0;
            ESP_ERROR_CHECK(rmt_transmit(rmt_chan, led_encoder, grb, sizeof(grb), &tx_conf));
        } else {
            // Input 0 : RGB LED off
            grb[0] = grb[1] = grb[2] = 0;
            ESP_ERROR_CHECK(rmt_transmit(rmt_chan, led_encoder, grb, sizeof(grb), &tx_conf));
        }
    }
}

