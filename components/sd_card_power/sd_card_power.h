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
    ESP_LOGI("SDCardPower", "Power control pin set to %d", pin);
  }
  
 protected:
  int power_ctrl_pin_{-1};
};

}  // namespace sd_card_power
}  // namespace esphome

