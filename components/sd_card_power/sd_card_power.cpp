#include "sd_card_power.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sd_card_power {

static const char *TAG = "sd_card_power";

void SDCardPower::setup() {
  this->configure_gpio_();
  this->turn_on();
  delay(2000);  // Increased delay to 2 seconds
  ESP_LOGI(TAG, "SD Card power component initialized, power ON at boot");
}

// ... (rest of the code remains the same)

}  // namespace sd_card_power
}  // namespace esphome
