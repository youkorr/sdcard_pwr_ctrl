import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ['esp32']
MULTI_CONF = True

sd_mmc_card_ns = cg.esphome_ns.namespace('sd_mmc_card')
SdMmc = sd_mmc_card_ns.class_('SdMmc', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SdMmc),
    cv.Required('clk_pin'): cv.gpio_pin,
    cv.Required('cmd_pin'): cv.gpio_pin,
    cv.Required('data0_pin'): cv.gpio_pin,
    cv.Optional('data1_pin'): cv.gpio_pin,
    cv.Optional('data2_pin'): cv.gpio_pin,
    cv.Optional('data3_pin'): cv.gpio_pin,
    cv.Optional('power_ctrl_pin'): cv.gpio_pin,
    cv.Optional('mode_1bit', default=False): cv.boolean,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    cg.add(var.set_clk_pin(config['clk_pin']))
    cg.add(var.set_cmd_pin(config['cmd_pin']))
    cg.add(var.set_data0_pin(config['data0_pin']))
    
    if 'data1_pin' in config:
        cg.add(var.set_data1_pin(config['data1_pin']))
    if 'data2_pin' in config:
        cg.add(var.set_data2_pin(config['data2_pin']))
    if 'data3_pin' in config:
        cg.add(var.set_data3_pin(config['data3_pin']))
    
    if 'power_ctrl_pin' in config:
        cg.add(var.set_power_ctrl_pin(config['power_ctrl_pin']))
    
    cg.add(var.set_mode_1bit(config.get('mode_1bit', False)))
    
    yield cg.register_component(var, config)
