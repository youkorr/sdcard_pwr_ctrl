#include "sd_card_power.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  this->configure_gpio_();
  this->turn_on();
  delay(500);  // Add a delay after powering on
  ESP_LOGI(TAG, "SD Card power component initialized, power ON at boot");
}

void SDCardPower::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card Power:");
  ESP_LOGCONFIG(TAG, "  Power Pin: GPIO%d", SDCARD_PWR_CTRL);
  ESP_LOGCONFIG(TAG, "  Current State: %s", this->is_on_ ? "ON" : "OFF");
}

void SDCardPower::turn_on() {
  this->set_power_state_(true);
  ESP_LOGI(TAG, "SD Card power turned ON");
}

void SDCardPower::turn_off() {
  this->set_power_state_(false);
  ESP_LOGI(TAG, "SD Card power turned OFF");
}

void SDCardPower::configure_gpio_() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1ULL << SDCARD_PWR_CTRL);
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);
}

void SDCardPower::set_power_state_(bool state) {
  gpio_set_level(SDCARD_PWR_CTRL, state ? 1 : 0);
  this->is_on_ = state;
}

}  // namespace sd_card_power
}  // namespace esphome
