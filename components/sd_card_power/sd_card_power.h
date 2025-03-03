#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/gpio.h"

namespace esphome {
namespace sd_card_power {

#define SDCARD_PWR_CTRL GPIO_NUM_43
#define SDCARD_INTR_GPIO GPIO_NUM_44
#define SDCARD_OPEN_FILE_NUM_MAX 5

class SDCardPower : public Component {
 public:
  void setup() override;
  void dump_config() override;
  
  void turn_on();
  void turn_off();
  
  int8_t get_sdcard_intr_gpio() { return SDCARD_INTR_GPIO; }
  int8_t get_sdcard_open_file_num_max() { return SDCARD_OPEN_FILE_NUM_MAX; }
  int8_t get_sdcard_power_ctrl_gpio() { return SDCARD_PWR_CTRL; }

 protected:
  bool is_on_{false};
  
  void configure_gpio_();
  void set_power_state_(bool state);
};

}  // namespace sd_card_power
}  // namespace esphome
