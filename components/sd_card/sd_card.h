#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_types.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  void set_clk_pin(GPIOPin *pin) { clk_pin_ = pin; }
  void set_cmd_pin(GPIOPin *pin) { cmd_pin_ = pin; }
  void set_data0_pin(GPIOPin *pin) { data0_pin_ = pin; }
  void set_data1_pin(GPIOPin *pin) { data1_pin_ = pin; }
  void set_data2_pin(GPIOPin *pin) { data2_pin_ = pin; }
  void set_data3_pin(GPIOPin *pin) { data3_pin_ = pin; }
  void set_power_pin(GPIOPin *pin) { power_pin_ = pin; }
  void set_mode_1bit(bool mode) { mode_1bit_ = mode; }

  void setup() override;
  void dump_config() override;
  
  bool is_mounted() const { return mounted_; }

 protected:
  void init_power_pin_();
  void init_sd_card_();

  GPIOPin *clk_pin_{nullptr};
  GPIOPin *cmd_pin_{nullptr};
  GPIOPin *data0_pin_{nullptr};
  GPIOPin *data1_pin_{nullptr};
  GPIOPin *data2_pin_{nullptr};
  GPIOPin *data3_pin_{nullptr};
  GPIOPin *power_pin_{nullptr};
  bool mode_1bit_{true};
  bool mounted_{false};
  sdmmc_card_t *card_{nullptr};
};

}  // namespace sd_card
}  // namespace esphome
