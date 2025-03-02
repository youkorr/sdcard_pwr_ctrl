#pragma once
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_types.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  // Setters pour les numéros de pin bruts
  void set_clk_pin(uint8_t pin) { clk_pin_ = pin; }
  void set_cmd_pin(uint8_t pin) { cmd_pin_ = pin; }
  void set_data0_pin(uint8_t pin) { data0_pin_ = pin; }
  void set_data1_pin(uint8_t pin) { data1_pin_ = pin; }
  void set_data2_pin(uint8_t pin) { data2_pin_ = pin; }
  void set_data3_pin(uint8_t pin) { data3_pin_ = pin; }

  void set_power_pin(GPIOPin *pin) { power_pin_ = pin; }
  void set_mode_1bit(bool mode_1bit) { mode_1bit_ = mode_1bit; }

  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  void init_power_pin_();
  void init_sd_card_();
  

  // Stockage des numéros de pin bruts
  uint8_t clk_pin_;
  uint8_t cmd_pin_;
  uint8_t data0_pin_;
  uint8_t data1_pin_;
  uint8_t data2_pin_;
  uint8_t data3_pin_;
  
  GPIOPin *power_pin_{nullptr};
  bool mode_1bit_{false};
  bool mounted_{false};
  sdmmc_card_t *card_{nullptr};
  

};

}  // namespace sd_card
}  // namespace esphome


