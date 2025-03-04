import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ['esp32']
MULTI_CONF = True

sd_mmc_card_ns = cg.esphome_ns.namespace('sd_mmc_card')
SdMmc = sd_mmc_card_ns.class_('SdMmc', cg.Component)

def validate_gpio_pin(value):
    # Convertit le pin GPIO en numéro
    if isinstance(value, str) and value.startswith('GPIO'):
        value = int(value[4:])
    
    # Validation simple du pin
    if not (0 <= value <= 48):
        raise cv.Invalid(f"GPIO pin must be between 0 and 48, got {value}")
    return value

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SdMmc),
    cv.Optional('power_ctrl_pin'): validate_gpio_pin,  # Garder uniquement power_ctrl_pin
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    # Conversion de power_ctrl_pin si nécessaire
    if 'power_ctrl_pin' in config:
        cg.add(var.set_power_ctrl_pin(config['power_ctrl_pin']))

    yield cg.register_component(var, config)


