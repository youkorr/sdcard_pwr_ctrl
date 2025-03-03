#pragma once

#include "esphome.h"
#include "driver/gpio.h"

namespace esphome {
namespace sd_card_power {

class SDCardPower : public Component {
 public:
  void setup() override;
  void set_power(bool state);
  void set_power_ctrl_pin(int pin) { power_ctrl_pin_ = pin; }

 private:
  int power_ctrl_pin_;
};

}  // namespace sd_card_power
}  // namespace esphome

