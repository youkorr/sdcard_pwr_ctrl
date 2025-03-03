#include "sd_card_power.h"

namespace esphome {
namespace sd_card_power {

void SDCardPower::setup() {
  if (power_ctrl_pin_ >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << power_ctrl_pin_,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(power_ctrl_pin_, 1); // Active l'alimentation de la carte SD
  }
}

void SDCardPower::set_power(bool state) {
  gpio_set_level(power_ctrl_pin_, state ? 1 : 0);
}

}  // namespace sd_card_power
}  // namespace esphome

