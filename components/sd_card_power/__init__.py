import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import gpio
from esphome.const import CONF_ID

pwr_ctrl_sd_ns = cg.esphome_ns.namespace('pwr_ctrl_sd')
PwrCtrlSD = pwr_ctrl_sd_ns.class_('PwrCtrlSD', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PwrCtrlSD),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)


