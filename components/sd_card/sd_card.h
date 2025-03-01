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
    clk_pin_num_ = pin ? pin->get_pin() : -1; 
  }
  void set_cmd_pin(GPIOPin *pin) { 
    cmd_pin_ = pin; 
    cmd_pin_num_ = pin ? pin->get_pin() : -1; 
  }
  void set_data0_pin(GPIOPin *pin) { 
    data0_pin_ = pin; 
    data0_pin_num_ = pin ? pin->get_pin() : -1; 
  }
  void set_data1_pin(GPIOPin *pin) { 
    data1_pin_ = pin; 
    data1_pin_num_ = pin ? pin->get_pin() : -1; 
  }
  void set_data2_pin(GPIOPin *pin) { 
    data2_pin_ = pin; 
    data2_pin_num_ = pin ? pin->get_pin() : -1; 
  }
  void set_data3_pin(GPIOPin *
