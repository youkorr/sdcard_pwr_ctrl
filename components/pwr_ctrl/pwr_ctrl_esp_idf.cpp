#include "pwr_ctrl.h"


#ifdef USE_ESP_IDF

#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "driver/gpio.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pwr_ctrl {

// Définir un TAG pour les logs
static const char *TAG = "pwr_ctrl";

// Fonction setup pour initialiser le contrôle de l'alimentation de la carte SD
void SdMmcPowerCtrl::setup() {
  // Vérifie si une broche de contrôle d'alimentation est définie
  if (this->power_ctrl_pin_ >= 0) {
    // Configuration du GPIO pour contrôler l'alimentation de la carte SD
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << this->power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    // Applique la configuration du GPIO
    gpio_config(&gpio_cfg);
    // Mettez la broche à l'état bas (désactive l'alimentation)
    gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);
    // Log d'information
    ESP_LOGI(TAG, "SD Card power control enabled on GPIO %d", this->power_ctrl_pin_);
  }
}

}  // namespace pwr_ctrl
}  // namespace esphome

#endif  // USE_ESP_IDF
