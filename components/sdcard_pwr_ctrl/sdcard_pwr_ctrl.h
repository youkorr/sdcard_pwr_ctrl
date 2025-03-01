#ifndef ESPHOME_SDCARD_PWR_CTRL_H
#define ESPHOME_SDCARD_PWR_CTRL_H

#include "esphome.h"

namespace esphome {
namespace sdcard_pwr_ctrl {

class SDCardPowerControl : public Component {
 public:
  void setup() override;
  void set_power_pin(GPIOPin *pin) { this->power_pin_ = pin; }

 protected:
  GPIOPin *power_pin_{nullptr};
};

// Déclaration du schéma de configuration YAML
class SDCardPowerControlComponent : public Component {
 public:
  void set_power_pin(GPIOPin *pin) { this->power_pin_ = pin; }

  void setup() override {
    if (this->power_pin_ != nullptr) {
      this->power_pin_->setup();
      this->power_pin_->digital_write(true); // Activer l'alimentation (HIGH)
      ESP_LOGD("SDCardPowerControl", "Alimentation du lecteur SD activée via GPIO43");
    }
  }

 protected:
  GPIOPin *power_pin_{nullptr};
};

}  // namespace sdcard_pwr_ctrl
}  // namespace esphome

#endif  // ESPHOME_SDCARD_PWR_CTRL_H
