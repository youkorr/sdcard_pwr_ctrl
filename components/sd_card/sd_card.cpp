#include "sd_card.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"

namespace esphome {
namespace sd_card {

static const char *TAG = "sd_card";

void SDCard::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SD Card...");
  
  if (this->power_pin_ == nullptr) {
    ESP_LOGE(TAG, "Power pin not set!");
    this->mark_failed();
    return;
  }

  this->init_power_pin_();
  delay(500);  // Wait for power to stabilize
  this->init_sd_card_();
  this->update_text_sensors_();
}

void SDCard::loop() {
  this->update_text_sensors_();
}

void SDCard::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card:");
  LOG_PIN("  CLK Pin: ", this->clk_pin_);
  LOG_PIN("  CMD Pin: ", this->cmd_pin_);
  LOG_PIN("  D0 Pin: ", this->data0_pin_);
  LOG_PIN("  D1 Pin: ", this->data1_pin_);
  LOG_PIN("  D2 Pin: ", this->data2_pin_);
  LOG_PIN("  D3 Pin: ", this->data3_pin_);
  LOG_PIN("  Power Pin: ", this->power_pin_);
  ESP_LOGCONFIG(TAG, "  Mode: %s", this->mode_1bit_ ? "1-bit" : "4-bit");
  ESP_LOGCONFIG(TAG, "  Mounted: %s", YESNO(this->mounted_));
}

void SDCard::init_power_pin_() {
  this->power_pin_->setup();
  this->power_pin_->digital_write(true);  // Turn on SD card power
  ESP_LOGI(TAG, "SD Card power turned ON");
}

void SDCard::init_sd_card_() {
  // ... (le reste du code reste inchangé)
}

void SDCard::update_text_sensors_() {
  if (this->sd_card_type_sensor_ != nullptr && this->card_ != nullptr) {
    const char *card_type = "Unknown";
    switch (this->card_->type) {
      case SDMMC_CARD_TYPE_SDSC:
        card_type = "SDSC";
        break;
      case SDMMC_CARD_TYPE_SDHC:
        card_type = "SDHC";
        break;
      case SDMMC_CARD_TYPE_SDXC:
        card_type = "SDXC";
        break;
      default:
        break;
    }
    this->sd_card_type_sensor_->publish_state(card_type);
  }

  if (this->sd_card_status_sensor_ != nullptr) {
    this->sd_card_status_sensor_->publish_state(this->mounted_ ? "Mounted" : "Not Mounted");
  }
}

}  // namespace sd_card
}  // namespace esphome
