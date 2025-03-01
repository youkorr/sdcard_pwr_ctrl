#include "esp32s3box3_sd_card.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace esp32s3box3_sd_card {

static const char *TAG = "esp32s3box3_sd_card";

void ESP32S3BOX3SDCard::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ESP32-S3-BOX-3 SD Card...");
  
  this->init_power_pin_();
  delay(500);  // Wait for power to stabilize
  
  if (this->sd_mmc_ == nullptr) {
    ESP_LOGE(TAG, "SD MMC component not set!");
    this->mark_failed();
    return;
  }
}

void ESP32S3BOX3SDCard::dump_config() {
  ESP_LOGCONFIG(TAG, "ESP32-S3-BOX-3 SD Card:");
  ESP_LOGCONFIG(TAG, "  Power Pin: GPIO%d", SDCARD_PWR_CTRL);
  ESP_LOGCONFIG(TAG, "  CLK Pin: GPIO%d", ESP_SD_PIN_CLK);
  ESP_LOGCONFIG(TAG, "  CMD Pin: GPIO%d", ESP_SD_PIN_CMD);
  ESP_LOGCONFIG(TAG, "  D0 Pin: GPIO%d", ESP_SD_PIN_D0);
  ESP_LOGCONFIG(TAG, "  D1 Pin: GPIO%d", ESP_SD_PIN_D1);
  ESP_LOGCONFIG(TAG, "  D2 Pin: GPIO%d", ESP_SD_PIN_D2);
  ESP_LOGCONFIG(TAG, "  D3 Pin: GPIO%d", ESP_SD_PIN_D3);
}

void ESP32S3BOX3SDCard::init_power_pin_() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1ULL << SDCARD_PWR_CTRL);
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);
  
  gpio_set_level(SDCARD_PWR_CTRL, 1);  // Turn on SD card power
  ESP_LOGI(TAG, "SD Card power turned ON");
}

}  // namespace esp32s3box3_sd_card
}  // namespace esphome
