#include "sd_card_power.h"
#include "esphome/core/log.h"
#include "driver/gpio.h"
#include "esp_system.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  // Vérification de la validité du pin
  if (this->power_ctrl_pin_ < 0) {
    ESP_LOGE(TAG, "Invalid GPIO pin for SD Card Power Control!");
    return;
  }

  ESP_LOGI(TAG, "Configuring SD Card Power Control on pin %d", this->power_ctrl_pin_);

  // Configuration du GPIO pour le contrôle d'alimentation
  gpio_config_t gpio_cfg = {
    .pin_bit_mask = 1ULL << this->power_ctrl_pin_,  // Correction de l'ordre des champs
    .mode = GPIO_MODE_OUTPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
  };

  // Configuration du GPIO
  esp_err_t result = gpio_config(&gpio_cfg);
  if (result != ESP_OK) {
    ESP_LOGE(TAG, "Failed to configure GPIO pin %d. Error: %s", 
             this->power_ctrl_pin_, esp_err_to_name(result));
    return;
  }

  // Mise sous tension initial (logique active basse)
  result = gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);
  if (result != ESP_OK) {
    ESP_LOGE(TAG, "Failed to set initial GPIO level. Error: %s", 
             esp_err_to_name(result));
    return;
  }

  ESP_LOGI(TAG, "SD Card Power Control initialized and powered on");
}

void SDCardPower::set_power(bool state) {
  if (this->power_ctrl_pin_ < 0) {
    ESP_LOGE(TAG, "Power control pin not configured!");
    return;
  }

  // Logique active basse : 0 = ON, 1 = OFF
  int level = state ? 0 : 1;
  esp_err_t result = gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), level);
  
  if (result == ESP_OK) {
    ESP_LOGI(TAG, "SD Card Power %s (GPIO %d set to %d)", 
             state ? "ON" : "OFF", this->power_ctrl_pin_, level);
  } else {
    ESP_LOGE(TAG, "Failed to set SD Card Power state. Error: %s", 
             esp_err_to_name(result));
  }
}

}  // namespace sd_card_power
}  // namespace esphome

