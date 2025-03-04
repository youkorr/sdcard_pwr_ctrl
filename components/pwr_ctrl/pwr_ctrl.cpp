#include "pwr_ctrl.h"
#include "esphome/core/log.h"
#include "driver/gpio.h"

namespace esphome {
namespace pwr_ctrl {

static const char *TAG = "pwr_ctrl";

void SdMmcPowerCtrl::setup() {
  // Enable SDCard power if power control pin is configured
  if (this->power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << this->power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(static_cast<gpio_num_t>(this->power_ctrl_pin_), 0);
    ESP_LOGI(TAG, "SD Card power control enabled on GPIO %d", this->power_ctrl_pin_);
  }
}

}  // namespace pwr_ctrl
}  // namespace esphome
