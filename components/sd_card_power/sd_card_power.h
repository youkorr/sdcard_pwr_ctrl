#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/gpio.h"

namespace esphome {
namespace sd_card_power {

#define SDCARD_PWR_CTRL GPIO_NUM_43

class SDCardPower : public Component {
 public:
  void setup() override;
  void dump_config() override;
  
  void turn_on();
  void turn_off();
  
 protected:
  bool is_on_{false};
  
  void configure_gpio_();
  void set_power_state_(bool state);
};

}  // namespace sd_card_power
}  // namespace esphome
