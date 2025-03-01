#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sd_card_power {

class SDCardPower : public Component {
 public:
  void set_power_pin(GPIOPin *pin) { power_pin_ = pin; }
  void set_power_on_boot(bool power_on_boot) { power_on_boot_ = power_on_boot; }
  void set_inverted(bool inverted) { inverted_ = inverted; }
  
  void setup() override;
  void dump_config() override;
  
  // Déclarations seulement - l'implémentation sera dans le fichier .cpp
  void turn_on();
  void turn_off();
  
 protected:
  GPIOPin *power_pin_{nullptr};
  bool power_on_boot_{true};
  bool inverted_{false};
  
  bool is_on_{false};
  
  // Méthode interne pour écrire sur la broche avec inversion si nécessaire
  void write_state_(bool state) {
    is_on_ = state;
    this->power_pin_->digital_write(inverted_ ? !state : state);
  }
};

}  // namespace sd_card_power
}  // namespace esphome
