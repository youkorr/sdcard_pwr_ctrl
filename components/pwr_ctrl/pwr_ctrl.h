#pragma once

namespace esphome {
namespace pwr_ctrl {

class SdMmcPowerCtrl {
 public:
  // Déclaration de la fonction setup() générique
  void setup();

  // Déclaration de la fonction setup() spécifique à ESP-IDF
  void setup_idf_specific();
};

}  // namespace pwr_ctrl
}  // namespace esphome

