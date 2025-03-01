#pragma once
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "driver/sdmmc_types.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace sd_card {

class SDCard : public Component {
 public:
  void set_clk_pin(GPIOPin *pin) { 
    clk_pin_ = pin; 
    clk_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }
  void set_cmd_pin(GPIOPin *pin) { 
    cmd_pin_ = pin; 
    cmd_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }
  void set_data0_pin(GPIOPin *pin) { 
    data0_pin_ = pin; 
    data0_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }
  void set_data1_pin(GPIOPin *pin) { 
    data1_pin_ = pin; 
    data1_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }
  void set_data2_pin(GPIOPin *pin) { 
    data2_pin_ = pin; 
    data2_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }
  void set_data3_pin(GPIOPin *pin) { 
    data3_pin_ = pin; 
    data3_pin_num_ = pin ? pin->get_pin() : -1;  // Remplacement de get_gpio() par get_pin()
  }

  
  void set_power_pin(GPIOPin *pin) { power_pin_ = pin; }
  void set_mode_1bit(bool mode_1bit) { mode_1bit_ = mode_1bit; }
  void set_card_type_sensor(text_sensor::TextSensor *sensor) { sd_card_type_sensor_ = sensor; }
  void set_card_status_sensor(text_sensor::TextSensor *sensor) { sd_card_status_sensor_ = sensor; }

  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  void init_power_pin_();
  void init_sd_card_();
  void update_text_sensors_();

  // Variables membres
  GPIOPin *clk_pin_{nullptr};
  GPIOPin *cmd_pin_{nullptr};
  GPIOPin *data0_pin_{nullptr};
  GPIOPin *data1_pin_{nullptr};
  GPIOPin *data2_pin_{nullptr};
  GPIOPin *data3_pin_{nullptr};
  GPIOPin *power_pin_{nullptr};
  
  int clk_pin_num_{-1};
  int cmd_pin_num_{-1};
  int data0_pin_num_{-1};
  int data1_pin_num_{-1};
  int data2_pin_num_{-1};
  int data3_pin_num_{-1};
  
  bool mode_1bit_{false};
  bool mounted_{false};
  sdmmc_card_t *card_{nullptr};
  
  text_sensor::TextSensor *sd_card_type_sensor_{nullptr};
  text_sensor::TextSensor *sd_card_status_sensor_{nullptr};
};

}  // namespace sd_card
}  // namespace esphome


