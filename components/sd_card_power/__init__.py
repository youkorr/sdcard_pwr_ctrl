import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import gpio
from esphome.const import CONF_ID

sd_card_power_ns = cg.esphome_ns.namespace('sd_card_power')
SDCardPower = sd_card_power_ns.class_('SDCardPower', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCardPower),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)



