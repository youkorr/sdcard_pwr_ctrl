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
  this->init_sd_card_();
}

void SDCard::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card:");
  ESP_LOGCONFIG(TAG, "  CLK Pin: GPIO%d", this->clk_pin_);
  ESP_LOGCONFIG(TAG, "  CMD Pin: GPIO%d", this->cmd_pin_);
  ESP_LOGCONFIG(TAG, "  D0 Pin: GPIO%d", this->data0_pin_);
  ESP_LOGCONFIG(TAG, "  D1 Pin: GPIO%d", this->data1_pin_);
  ESP_LOGCONFIG(TAG, "  D2 Pin: GPIO%d", this->data2_pin_);
  ESP_LOGCONFIG(TAG, "  D3 Pin: GPIO%d", this->data3_pin_);
  ESP_LOGCONFIG(TAG, "  Power Pin: GPIO%d", this->power_pin_);
  ESP_LOGCONFIG(TAG, "  Mode: %s", this->mode_1bit_ ? "1-bit" : "4-bit");
  ESP_LOGCONFIG(TAG, "  Mounted: %s", YESNO(this->mounted_));
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

void SDCard::init_sd_card_() {
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  if (this->mode_1bit_) {
    host.flags = SDMMC_HOST_FLAG_1BIT;
  }
  host.max_freq_khz = SDMMC_FREQ_DEFAULT;

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = this->mode_1bit_ ? 1 : 4;
  slot_config.clk = static_cast<gpio_num_t>(this->clk_pin_);
  slot_config.cmd = static_cast<gpio_num_t>(this->cmd_pin_);
  slot_config.d0 = static_cast<gpio_num_t>(this->data0_pin_);
  if (!this->mode_1bit_) {
    slot_config.d1 = static_cast<gpio_num_t>(this->data1_pin_);
    slot_config.d2 = static_cast<gpio_num_t>(this->data2_pin_);
    slot_config.d3 = static_cast<gpio_num_t>(this->data3_pin_);
  }

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024
  };

  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &this->card_);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE(TAG, "Failed to mount filesystem.");
    } else {
      ESP_LOGE(TAG, "Failed to initialize the card (%s). "
               "Make sure SD card lines have pull-up resistors in place.",
               esp_err_to_name(ret));
    }
    return;
  }

  this->mounted_ = true;
  ESP_LOGI(TAG, "SD card mounted successfully");
}

}  // namespace sd_card
}  // namespace esphome
