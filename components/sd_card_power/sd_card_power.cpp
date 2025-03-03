#include "sd_card_power.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  if (this->power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << this->power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    
    esp_err_t result = gpio_config(&gpio_cfg);
    if (result == ESP_OK) {
      // Active l'alimentation de la carte SD (niveau 0 = ON par défaut)
      gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);
      ESP_LOGI(TAG, "SD Card Power Control initialized on pin %d", this->power_ctrl_pin_);
    } else {
      ESP_LOGE(TAG, "Failed to configure SD Card Power Control pin %d, error: %d", 
               this->power_ctrl_pin_, result);
    }
  } else {
    ESP_LOGE(TAG, "SD Card Power Control pin not configured!");
  }
}

void SDCardPower::set_power(bool state) {
  if (this->power_ctrl_pin_ >= 0) {
    // Niveau logique : 0 = ON, 1 = OFF (selon la logique du circuit)
    // Si votre circuit est différent, vous devrez peut-être inverser cette logique
    int level = state ? 0 : 1;
    esp_err_t result = gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), level);
    
    if (result == ESP_OK) {
      ESP_LOGI(TAG, "SD Card Power %s", state ? "ON" : "OFF");
    } else {
      ESP_LOGE(TAG, "Failed to set SD Card Power state, error: %d", result);
    }
  } else {
    ESP_LOGE(TAG, "Cannot set power state: power control pin not configured");
  }
}

}  // namespace sd_card_power
}  // namespace esphome

