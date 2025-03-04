#include "pwr_ctrl.h"
#include "esp_log.h"
#include "driver/gpio.h"  // Pour la gestion GPIO spécifique à ESP-IDF

#ifdef USE_ESP_IDF  // Assure-toi que cette directive conditionnelle est bien placée

namespace esphome {
namespace pwr_ctrl {

void SdMmcPowerCtrl::setup_idf_specific() {
  // Vérifie si power_ctrl_pin_ a bien été défini
  if (this->power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << this->power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);  // Logique spécifique à ESP-IDF
    ESP_LOGI("sd_mmc_card", "SD Card power control enabled on GPIO %d", this->power_ctrl_pin_);
  }
}

}  // namespace pwr_ctrl
}  // namespace esphome

#endif  // USE_ESP_IDF


