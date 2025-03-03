#include "sd_card.h"
#include "esphome/core/log.h"

#include <driver/gpio.h>
#include <driver/sdmmc_host.h>
#include <driver/sdspi_host.h>
#include <sdmmc_cmd.h>
#include <esp_vfs_fat.h>

namespace esphome {
namespace sd_card {

static const char *const TAG = "sd_card";

void SDCard::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SD Card...");
  
  if (this->power_pin_ == nullptr) {
    ESP_LOGE(TAG, "Power pin not set!");
    this->mark_failed();
    return;
  }

  this->init_power_pin_();
  delay(500);
  this->init_sd_card_();
  
}


void SDCard::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card:");
  ESP_LOGCONFIG(TAG, "  CLK Pin: GPIO%d", this->clk_pin_);  // Correction
  ESP_LOGCONFIG(TAG, "  CMD Pin: GPIO%d", this->cmd_pin_);  // Correction
  ESP_LOGCONFIG(TAG, "  D0 Pin: GPIO%d", this->data0_pin_); // Correction
  ESP_LOGCONFIG(TAG, "  D1 Pin: GPIO%d", this->data1_pin_); // Correction
  ESP_LOGCONFIG(TAG, "  D2 Pin: GPIO%d", this->data2_pin_); // Correction
  ESP_LOGCONFIG(TAG, "  D3 Pin: GPIO%d", this->data3_pin_); // Correction
  LOG_PIN("  Power Pin: ", this->power_pin_);
  ESP_LOGCONFIG(TAG, "  Mode: %s", this->mode_1bit_ ? "1-bit" : "4-bit");
  ESP_LOGCONFIG(TAG, "  Mounted: %s", YESNO(this->mounted_));
}

void SDCard::init_power_pin_() {
  this->power_pin_->setup();
  this->power_pin_->digital_write(true);
  ESP_LOGI(TAG, "SD Card power turned ON");
}

void SDCard::init_sd_card_() {
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  if (this->mode_1bit_) {
    host.flags = SDMMC_HOST_FLAG_1BIT;
  }
  host.max_freq_khz = SDMMC_FREQ_DEFAULT;

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = this->mode_1bit_ ? 1 : 4;
  
  // Assignation corrigée des pins
  slot_config.clk = static_cast<gpio_num_t>(this->clk_pin_);   // Correction
  slot_config.cmd = static_cast<gpio_num_t>(this->cmd_pin_);   // Correction
  slot_config.d0 = static_cast<gpio_num_t>(this->data0_pin_);  // Correction

  if (!this->mode_1bit_) {
    slot_config.d1 = static_cast<gpio_num_t>(this->data1_pin_); // Correction
    slot_config.d2 = static_cast<gpio_num_t>(this->data2_pin_); // Correction
    slot_config.d3 = static_cast<gpio_num_t>(this->data3_pin_); // Correction
  }

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024
  };

  sdmmc_card_t *card = nullptr;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
  this->card_ = card;

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE(TAG, "Failed to mount filesystem.");
    } else {
      ESP_LOGE(TAG, "Failed to initialize the card (%s)", esp_err_to_name(ret));
    }
    return;
  }

  this->mounted_ = true;
  ESP_LOGI(TAG, "SD card mounted successfully");

}

}  // namespace sd_card
}  // namespace esphome

