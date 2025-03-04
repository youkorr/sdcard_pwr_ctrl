#pragma once

namespace esphome {
namespace pwr_ctrl {

class SdMmcPowerCtrl {
 public:
  int power_ctrl_pin_;  // Déclare la variable ici, elle doit être définie dans ton code ou via la configuration

  // Déclaration de la fonction setup() générique
  void setup();

  // Déclaration de la fonction setup() spécifique à ESP-IDF
  void setup_idf_specific();
};

}  // namespace pwr_ctrl
}  // namespace esphome


