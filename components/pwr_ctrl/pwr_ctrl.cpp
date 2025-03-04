#include "pwr_ctrl.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pwr_ctrl {

void SdMmcPowerCtrl::setup() {
  // Logique générique de setup pour le contrôleur d'alimentation
  ESP_LOGI("pwr_ctrl", "Setup générique du contrôleur d'alimentation.");
  // Ici tu peux ajouter une logique commune qui ne dépend pas d'ESP-IDF
}

}  // namespace pwr_ctrl
}  // namespace esphome

