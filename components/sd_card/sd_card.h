#pragma once

#include "esphome/core/component.h"
#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  void set_clk_pin(int pin) { clk_pin_ = pin; }
  void set_cmd_pin(int pin) { cmd_pin_ = pin; }
  void set_data0_pin(int pin) { data0_pin_ = pin; }
  void set_data1_pin(int pin) { data1_pin_ = pin; }
  void set_data2_pin(int pin) { data2_pin_ = pin; }
  void set_data3_pin(int pin) { data3_pin_ = pin; }
  void set_power_pin(int pin) { power_pin_ = pin; }
  void set_mode_1bit(bool mode) { mode_1bit_ = mode; }

  void setup() override;
  void dump_config() override;
  
  bool is_mounted() const { return mounted_; }

 protected:
  void init_power_pin_();
  void init_sd_card_();

  int clk_pin_{-1};
  int cmd_pin_{-1};
  int data0_pin_{-1};
  int data1_pin_{-1};
  int data2_pin_{-1};
  int data3_pin_{-1};
  int power_pin_{-1};
  bool mode_1bit_{true};
  bool mounted_{false};
  sdmmc_card_t *card_{nullptr};
};

}  // namespace sd_card
}  // namespace esphome
