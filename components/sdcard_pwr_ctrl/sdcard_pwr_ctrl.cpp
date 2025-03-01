#include "sdcard_pwr_ctrl.h"

namespace esphome {
namespace sdcard_pwr_ctrl {

void SDCardPowerControl::setup() {
  if (this->power_pin_ != nullptr) {
    this->power_pin_->setup();
    this->power_pin_->digital_write(true); // Activer l'alimentation (HIGH)
    ESP_LOGD("SDCardPowerControl", "Alimentation du lecteur SD activée via GPIO43");
  }
}

}  // namespace sdcard_pwr_ctrl
}  // namespace esphome
