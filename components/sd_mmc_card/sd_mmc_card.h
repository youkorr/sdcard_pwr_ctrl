#pragma once

#include "esphome/core/component.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_types.h"
#include "esp_vfs_fat.h"

namespace esphome {
namespace sd_mmc_card {

class SdMmc : public Component {
 public:
  void setup() override;
  void dump_config() override;

  void set_clk_pin(int8_t pin) { clk_pin_ = pin; }
  void set_cmd_pin(int8_t pin) { cmd_pin_ = pin; }
  void set_data0_pin(int8_t pin) { data0_pin_ = pin; }
  void set_data1_pin(int8_t pin) { data1_pin_ = pin; }
  void set_data2_pin(int8_t pin) { data2_pin_ = pin; }
  void set_data3_pin(int8_t pin) { data3_pin_ = pin; }
  void set_mode_1bit(bool mode) { mode_1bit_ = mode; }
  void set_power_ctrl_pin(int8_t pin) { power_ctrl_pin_ = pin; } // Ajout de set_power_ctrl_pin

 protected:
  int8_t clk_pin_{-1};
  int8_t cmd_pin_{-1};
  int8_t data0_pin_{-1};
  int8_t data1_pin_{-1};
  int8_t data2_pin_{-1};
  int8_t data3_pin_{-1};  // Assure-toi qu'il est bien là
  int8_t power_ctrl_pin_{-1};  // Assure-toi qu'il est bien là
  bool mode_1bit_{false};
};

}  // namespace sd_mmc_card
}  // namespace esphome

   
