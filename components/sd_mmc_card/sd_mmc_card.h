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

  void set_power_ctrl_pin(int8_t pin) { power_ctrl_pin_ = pin; }  // Garder uniquement power_ctrl_pin

 protected:
  int8_t power_ctrl_pin_{-1};  // Garder uniquement power_ctrl_pin
};

}  // namespace sd_mmc_card
}  // namespace esphome


   
