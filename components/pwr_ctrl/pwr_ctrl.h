#pragma once

#include "esphome/core/component.h"
#include "driver/gpio.h"

namespace esphome {
namespace pwr_ctrl {

class SdMmcPowerCtrl : public Component {
 public:
  void setup() override;

  void set_power_ctrl_pin(int8_t pin) { power_ctrl_pin_ = pin; }

 protected:
  int8_t power_ctrl_pin_{-1};
};

}  // namespace pwr_ctrl
}  // namespace esphome
