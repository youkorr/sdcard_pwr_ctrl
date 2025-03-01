#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sdcard/sdcard.h"
#include "driver/gpio.h"

namespace esphome {
namespace esp32s3box3_sd_card {

#define SDCARD_PWR_CTRL             GPIO_NUM_43
#define ESP_SD_PIN_CLK              GPIO_NUM_11
#define ESP_SD_PIN_CMD              GPIO_NUM_14
#define ESP_SD_PIN_D0               GPIO_NUM_9
#define ESP_SD_PIN_D1               GPIO_NUM_13
#define ESP_SD_PIN_D2               GPIO_NUM_42
#define ESP_SD_PIN_D3               GPIO_NUM_12

class ESP32S3BOX3SDCard : public Component {
 public:
  void setup() override;
  void dump_config() override;
  
  sdcard::SDCard *get_sdcard() { return &this->sd_card_; }

 protected:
  void init_power_pin_();
  void init_sd_card_();

  sdcard::SDCard sd_card_;
};

}  // namespace esp32s3box3_sd_card
}  // namespace esphome
