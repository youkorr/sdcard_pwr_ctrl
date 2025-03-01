#include "esp32s3box3_sd_card.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

namespace esphome {
namespace esp32s3box3_sd_card {

static const char *TAG = "esp32s3box3_sd_card";

void ESP32S3BOX3SDCard::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ESP32-S3-BOX-3 SD Card...");
  
  this->init_power_pin_();
  delay(500);  // Wait for power to stabilize
  this->init_sd_card_();
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

void ESP32S3BOX3SDCard::init_sd_card_() {
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  host.flags = SDMMC_HOST_FLAG_1BIT;
  host.max_freq_khz = SDMMC_FREQ_DEFAULT;

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 1;
  slot_config.clk = ESP_SD_PIN_CLK;
  slot_config.cmd = ESP_SD_PIN_CMD;
  slot_config.d0 = ESP_SD_PIN_D0;

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024
  };

  sdmmc_card_t *card;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

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

  ESP_LOGI(TAG, "SD card mounted successfully");
  this->sd_card_.set_card_info(card);
}

}  // namespace esp32s3box3_sd_card
}  // namespace esphome
