#pragma once
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_types.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  void set_clk_pin(GPIOPin *pin) { 
    clk_pin_ = pin; 
    clk_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }
  void set_cmd_pin(GPIOPin *pin) { 
    cmd_pin_ = pin; 
    cmd_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }
  void set_data0_pin(GPIOPin *pin) { 
    data0_pin_ = pin; 
    data0_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }
  void set_data1_pin(GPIOPin *pin) { 
    data1_pin_ = pin; 
    data1_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }
  void set_data2_pin(GPIOPin *pin) { 
    data2_pin_ = pin; 
    data2_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }
  void set_data3_pin(GPIOPin *pin) {
    data3_pin_ = pin;
    data3_pin_num_ = pin ? pin->get_gpio() : -1;  // Correction: get_pin() -> get_gpio()
  }

  // Déclaration des autres méthodes nécessaires, comme setup(), loop(), dump_config(), etc.
  void setup() override;
  void dump_config() override;

 protected:
  // Déclaration des variables membres
  GPIOPin *clk_pin_{nullptr};
  GPIOPin *cmd_pin_{nullptr};
  GPIOPin *data0_pin_{nullptr};
  GPIOPin *data1_pin_{nullptr};
  GPIOPin *data2_pin_{nullptr};
  GPIOPin *data3_pin_{nullptr};
  
  int clk_pin_num_{-1};
  int cmd_pin_num_{-1};
  int data0_pin_num_{-1};
  int data1_pin_num_{-1};
  int data2_pin_num_{-1};
  int data3_pin_num_{-1};
};

}  // namespace sd_card
}  // namespace esphome


