#include "sd_mmc_card.h"
#include "esphome/core/log.h"
#include "driver/gpio.h"
#include "esp_vfs_fat.h"

namespace esphome {
namespace sd_mmc_card {

static const char *TAG = "sd_mmc_card";

void SdMmc::setup() {
  // Enable SDCard power if power control pin is configured
  if (power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(static_cast<gpio_num_t>(power_ctrl_pin_), 0);
    ESP_LOGI(TAG, "SD Card power control enabled on GPIO %d", power_ctrl_pin_);
  }

  // Reste de votre logique d'initialisation de la carte SD
  ESP_LOGI(TAG, "SD Card setup completed");
}

void SdMmc::dump_config() {
  ESP_LOGCONFIG(TAG, "SD MMC Card Configuration:");
  ESP_LOGCONFIG(TAG, "  CLK Pin: %d", clk_pin_);
  ESP_LOGCONFIG(TAG, "  CMD Pin: %d", cmd_pin_);
  ESP_LOGCONFIG(TAG, "  DATA0 Pin: %d", data0_pin_);
  
  if (data1_pin_ >= 0) 
    ESP_LOGCONFIG(TAG, "  DATA1 Pin: %d", data1_pin_);
  if (data2_pin_ >= 0) 
    ESP_LOGCONFIG(TAG, "  DATA2 Pin: %d", data2_pin_);
  if (data3_pin_ >= 0) 
    ESP_LOGCONFIG(TAG, "  DATA3 Pin: %d", data3_pin_);
  
  if (power_ctrl_pin_ >= 0)
    ESP_LOGCONFIG(TAG, "  Power Control Pin: %d", power_ctrl_pin_);
  
  ESP_LOGCONFIG(TAG, "  Mode: %s", mode_1bit_ ? "1-bit" : "4-bit");
}

}  // namespace sd_mmc_card
}  // namespace esphome
