#include "sd_card.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sd_card {

static const char *TAG = "sd_card";

void SDCard::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SD Card...");
  
  if (this->power_pin_ < 0) {
    ESP_LOGE(TAG, "Power pin not set!");
    this->mark_failed();
    return;
  }

  this->init_power_pin_();
  delay(500);  // Wait for power to stabilize
  
  if (this->sd_mmc_ == nullptr) {
    ESP_LOGE(TAG, "SD MMC component not set!");
    this->mark_failed();
    return;
  }
}

void SDCard::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card:");
  ESP_LOGCONFIG(TAG, "  Power Pin: GPIO%d", this->power_pin_);
  ESP_LOGCONFIG(TAG, "  Mounted: %s", YESNO(this->is_mounted()));
}

void SDCard::init_power_pin_() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1ULL << this->power_pin_);
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);
  
  gpio_set_level(static_cast<gpio_num_t>(this->power_pin_), 1);  // Turn on SD card power
  ESP_LOGI(TAG, "SD Card power turned ON");
}

}  // namespace sd_card
}  // namespace esphome
