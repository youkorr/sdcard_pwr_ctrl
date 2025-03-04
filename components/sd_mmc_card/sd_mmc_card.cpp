#include "sd_mmc_card.h"
#include "esphome/core/log.h"
#include "driver/gpio.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

namespace esphome {
namespace sd_mmc_card {

static const char *TAG = "sd_mmc_card";

void SdMmc::setup() {
  // Enable SDCard power if power control pin is configured
  if (this->power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << this->power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);
    ESP_LOGI(TAG, "SD Card power control enabled on GPIO %d", this->power_ctrl_pin_);
  }

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false, 
      .max_files = 5, 
      .allocation_unit_size = 16 * 1024
  };

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

  // Configuration des pins
  slot_config.clk = static_cast<gpio_num_t>(clk_pin_);
  slot_config.cmd = static_cast<gpio_num_t>(cmd_pin_);
  slot_config.d0 = static_cast<gpio_num_t>(data0_pin_);
  
  if (!mode_1bit_) {
    slot_config.d1 = static_cast<gpio_num_t>(data1_pin_);
    slot_config.d2 = static_cast<gpio_num_t>(data2_pin_);
    slot_config.d3 = static_cast<gpio_num_t>(data3_pin_);
  }

  // Ajustement du mode 1-bit si nécessaire
  host.flags = mode_1bit_ ? SDMMC_HOST_FLAG_1BIT : 0;

  // Tentative de montage de la carte SD
  sdmmc_card_t* card = NULL;
  esp_err_t result = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
  
  if (result != ESP_OK) {
    ESP_LOGE(TAG, "Failed to mount SD card. Error: %s", esp_err_to_name(result));
    return;
  }

  ESP_LOGI(TAG, "SD Card mounted successfully");
}

void SdMmc::dump_config() {
  ESP_LOGCONFIG(TAG, "SD MMC Card Configuration:");
  ESP_LOGCONFIG(TAG, "  CLK Pin: %d", clk_pin_);
  ESP_LOGCONFIG(TAG, "  CMD Pin: %d", cmd_pin_);
  ESP_LOGCONFIG(TAG, "  DATA0 Pin: %d", data0_pin_);
  
  if (!mode_1bit_) {
    if (data1_pin_ >= 0) 
      ESP_LOGCONFIG(TAG, "  DATA1 Pin: %d", data1_pin_);
    if (data2_pin_ >= 0) 
      ESP_LOGCONFIG(TAG, "  DATA2 Pin: %d", data2_pin_);
    if (data3_pin_ >= 0) 
      ESP_LOGCONFIG(TAG, "  DATA3 Pin: %d", data3_pin_);
  }
  
  if (power_ctrl_pin_ >= 0)
    ESP_LOGCONFIG(TAG, "  Power Control Pin: %d", power_ctrl_pin_);
  
bool mode_1bit_{false};  // Initialisation correcte
};

}  // namespace sd_mmc_card
}  // namespace esphome
