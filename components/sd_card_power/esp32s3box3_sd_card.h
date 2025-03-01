#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sd_mmc_card/sd_mmc_card.h"
#include "driver/gpio.h"

namespace esphome {
namespace esp32s3box3_sd_card {

class ESP32S3BOX3SDCard : public Component {
 public:
  void set_sd_mmc_card(sd_mmc_card::SdMmc *sd_mmc) { sd_mmc_ = sd_mmc; }
  void set_power_pin(int pin) { power_pin_ = pin; }
  void setup() override;
  void dump_config() override;
  
  bool is_mounted() const { return sd_mmc_ != nullptr && sd_mmc_->is_mounted(); }

 protected:
  void init_power_pin_();

  sd_mmc_card::SdMmc *sd_mmc_{nullptr};
  int power_pin_{-1};
};

}  // namespace esp32s3box3_sd_card
}  // namespace esphome
