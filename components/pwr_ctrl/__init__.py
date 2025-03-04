import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ['esp32']
MULTI_CONF = True

pwr_ctrl_ns = cg.esphome_ns.namespace('pwr_ctrl')
SdMmcPowerCtrl = pwr_ctrl_ns.class_('SdMmcPowerCtrl', cg.Component)

def validate_gpio_pin(value):
    # Validation simple du pin GPIO
    if isinstance(value, str) and value.startswith('GPIO'):
        value = int(value[4:])
    if not (0 <= value <= 48):
        raise cv.Invalid(f"GPIO pin must be between 0 and 48, got {value}")
    return value

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SdMmcPowerCtrl),
    cv.Required('power_ctrl_pin'): validate_gpio_pin,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_power_ctrl_pin(config['power_ctrl_pin']))
    yield cg.register_component(var, config)
