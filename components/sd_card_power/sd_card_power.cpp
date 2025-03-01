#include "sd_card_power.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  if (this->power_pin_ == nullptr) {
    ESP_LOGE(TAG, "Power pin not set!");
    this->mark_failed();
    return;
  }
  
  this->power_pin_->setup();
  
  if (this->power_on_boot_) {
    this->turn_on();
  } else {
    this->turn_off();
  }
  
  ESP_LOGI(TAG, "SD Card power component initialized, power %s at boot", 
           this->power_on_boot_ ? "ON" : "OFF");
}

void SDCardPower::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card Power:");
  LOG_PIN("  Power Pin: ", this->power_pin_);
  ESP_LOGCONFIG(TAG, "  Power On Boot: %s", this->power_on_boot_ ? "YES" : "NO");
  ESP_LOGCONFIG(TAG, "  Inverted: %s", this->inverted_ ? "YES" : "NO");
  ESP_LOGCONFIG(TAG, "  Current State: %s", this->is_on_ ? "ON" : "OFF");
}

void SDCardPower::turn_on() {
  if (this->power_pin_ != nullptr) {
    this->write_state_(true);
    ESP_LOGI(TAG, "SD Card power turned ON");
  }
}

void SDCardPower::turn_off() {
  if (this->power_pin_ != nullptr) {
    this->write_state_(false);
    ESP_LOGI(TAG, "SD Card power turned OFF");
  }
}

}  // namespace sd_card_power
}  // namespace esphome
