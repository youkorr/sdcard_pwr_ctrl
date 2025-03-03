#pragma once

#include "esphome.h"
#include "driver/gpio.h"

#define SDCARD_PWR_CTRL GPIO_NUM_43

namespace esphome {
namespace sd_card_power {

class SDCardPower : public Component {
 public:
  void setup() override;
  void set_power(bool state);
};

}  // namespace sd_card_power
}  // namespace esphome

