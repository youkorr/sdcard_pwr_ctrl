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
    cv.Required('clk_pin'): validate_gpio_pin,
    cv.Required('cmd_pin'): validate_gpio_pin,
    cv.Required('data0_pin'): validate_gpio_pin,
    cv.Optional('data1_pin'): validate_gpio_pin,
    cv.Optional('data2_pin'): validate_gpio_pin,
    cv.Optional('data3_pin'): validate_gpio_pin,
    cv.Optional('power_ctrl_pin'): validate_gpio_pin,
    cv.Optional('mode_1bit', default=False): cv.boolean,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    # Conversion des valeurs de pin si nécessaire
    def convert_pin(pin):
        return int(pin[4:]) if isinstance(pin, str) and pin.startswith('GPIO') else pin

    cg.add(var.set_clk_pin(convert_pin(config['clk_pin'])))
    cg.add(var.set_cmd_pin(convert_pin(config['cmd_pin'])))
    cg.add(var.set_data0_pin(convert_pin(config['data0_pin'])))
    
    if 'data1_pin' in config:
        cg.add(var.set_data1_pin(convert_pin(config['data1_pin'])))
    if 'data2_pin' in config:
        cg.add(var.set_data2_pin(convert_pin(config['data2_pin'])))
    if 'data3_pin' in config:
        cg.add(var.set_data3_pin(convert_pin(config['data3_pin'])))
    
    if 'power_ctrl_pin' in config:
        cg.add(var.set_power_ctrl_pin(convert_pin(config['power_ctrl_pin'])))
    
    cg.add(var.set_mode_1bit(config.get('mode_1bit', False)))
    
    yield cg.register_component(var, config)
