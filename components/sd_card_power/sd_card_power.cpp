#include "sd_card_power.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  // Enable SDCard power
  if (get_sdcard_power_ctrl_gpio() >= 0) {
    gpio_config_t gpio_cfg = {
      .pin_bit_mask = 1ULL << get_sdcard_power_ctrl_gpio(),
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&gpio_cfg);
    gpio_set_level(get_sdcard_power_ctrl_gpio(), 0);
  }
  
  this->turn_on();
  delay(2000);
  ESP_LOGI(TAG, "SD Card power component initialized, power ON at boot");
}

void SDCardPower::configure_gpio_() {
  // GPIO configuration is now handled in setup()
}

void SDCardPower::set_power_state_(bool state) {
  if (get_sdcard_power_ctrl_gpio() >= 0) {
    gpio_set_level(get_sdcard_power_ctrl_gpio(), state ? 1 : 0);
    is_on_ = state;
  }
}

void SDCardPower::turn_on() {
  set_power_state_(true);
  ESP_LOGI(TAG, "SD Card power turned ON");
}

void SDCardPower::turn_off() {
  set_power_state_(false);
  ESP_LOGI(TAG, "SD Card power turned OFF");
}

void SDCardPower::dump_config() {
  ESP_LOGCONFIG(TAG, "SD Card Power:");
  ESP_LOGCONFIG(TAG, "  Power Control GPIO: %d", get_sdcard_power_ctrl_gpio());
  ESP_LOGCONFIG(TAG, "  Interrupt GPIO: %d", get_sdcard_intr_gpio());
  ESP_LOGCONFIG(TAG, "  Max Open Files: %d", get_sdcard_open_file_num_max());
}

}  // namespace sd_card_power
}  // namespace esphome
