#pragma once

#include "esphome/core/component.h"
#include "driver/gpio.h"

namespace esphome {
namespace sd_card_power {

class SDCardPower : public Component {
 public:
  SDCardPower() = default;
  
  void setup() override;
  void set_power(bool state);
  
  void set_power_ctrl_pin(int pin) { 
    this->power_ctrl_pin_ = pin; 
  }
  
 protected:
  int power_ctrl_pin_{GPIO_NUM_43};  // Valeur par défaut basée sur votre configuration
};

}  // namespace sd_card_power
}  // namespace esphome

