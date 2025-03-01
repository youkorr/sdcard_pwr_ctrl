#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_types.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  void set_clk_pin(uint8_t pin) { clk_pin_number_ = pin; }
  void set_cmd_pin(uint8_t pin) { cmd_pin_number_ = pin; }
  void set_data0_pin(uint8_t pin) { data0_pin_number_ = pin; }
  void set_data1_pin(uint8_t pin) { data1_pin_number_ = pin; }
  void set_data2_pin(uint8_t pin) { data2_pin_number_ = pin; }
  void set_data3_pin(uint8_t pin) { data3_pin_number_ = pin; }
  void set_power_pin(GPIOPin *pin) { power_pin_ = pin; }
  void set_mode_1bit(bool mode) { mode_1bit_ = mode; }

  void setup() override;
  void dump_config() override;
  
  bool is_mounted() const { return mounted_; }

 protected:
  void init_power_pin_();
  void init_sd_card_();

  uint8_t clk_pin_number_{0};
  uint8_t cmd_pin_number_{0};
  uint8_t data0_pin_number_{0};
  uint8_t data1_pin_number_{0};
  uint8_t data2_pin_number_{0};
  uint8_t data3_pin_number_{0};
  uint8_t power_pin_number_{0};
  GPIOPin *power_pin_{nullptr};
  bool mode_1bit_{true};
  bool mounted_{false};
  sdmmc_card_t *card_{nullptr};
};

}  // namespace sd_card
}  // namespace esphome
