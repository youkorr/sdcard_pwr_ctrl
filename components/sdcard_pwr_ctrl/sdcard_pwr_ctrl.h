#ifndef ESPHOME_SDCARD_PWR_CTRL_H
#define ESPHOME_SDCARD_PWR_CTRL_H

#include "esphome.h"

namespace esphome {
namespace sdcard_pwr_ctrl {

class SDCardPowerControl : public Component {
 public:
  void set_power_pin(GPIOPin *pin) { this->power_pin_ = pin; }
  void setup() override;

 protected:
  GPIOPin *power_pin_{nullptr};
};

}  // namespace sdcard_pwr_ctrl
}  // namespace esphome

#endif  // ESPHOME_SDCARD_PWR_CTRL_H
