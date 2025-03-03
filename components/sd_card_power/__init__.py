import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
import esphome.components.esp32 as esp32

CONF_POWER_CTRL_PIN = 'power_ctrl_pin'
DEPENDENCIES = ['esp32']

sd_card_power_ns = cg.esphome_ns.namespace('sd_card_power')
SDCardPower = sd_card_power_ns.class_('SDCardPower', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCardPower),
    cv.Optional(CONF_POWER_CTRL_PIN, default=43): cv.int_range(min=0, max=48),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_power_ctrl_pin(config[CONF_POWER_CTRL_PIN]))
    yield cg.register_component(var, config)



