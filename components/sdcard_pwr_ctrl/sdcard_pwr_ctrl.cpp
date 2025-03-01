#include "sdcard_pwr_ctrl.h"

namespace esphome {
namespace sdcard_pwr_ctrl {

void SDCardPowerControl::setup() {
  if (this->power_pin_ != nullptr) {
    this->power_pin_->setup();
    this->power_pin_->digital_write(true); // Activer l'alimentation (HIGH)
    ESP_LOGD("SDCardPowerControl", "Alimentation du lecteur SD activée via GPIO43");
  }
}

// Enregistrer le composant dans ESPHome
static const esphome::ComponentSchema SCHEMA = {
    .name = "sdcard_pwr_ctrl",
    .config_schema = {
        {"power_pin", esphome::config_validation::SchemaType::GPIO_PIN},
    },
    .create_component = [](const esphome::Config &config) -> esphome::Component * {
      auto *component = new SDCardPowerControl();
      component->set_power_pin(config["power_pin"].as<esphome::GPIOPin *>());
      return component;
    },
};

}  // namespace sdcard_pwr_ctrl
}  // namespace esphome
