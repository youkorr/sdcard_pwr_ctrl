import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_ID

DEPENDENCIES = ["esp32"]

CONF_SD_CARD_ID = "sd_card_id"
sd_card_ns = cg.esphome_ns.namespace("sd_card")
SDCard = sd_card_ns.class_("SDCard", cg.Component)

# Custom constants
CONF_CLK_PIN = "clk_pin"
CONF_CMD_PIN = "cmd_pin"
CONF_DATA0_PIN = "data0_pin"
CONF_DATA1_PIN = "data1_pin"
CONF_DATA2_PIN = "data2_pin"
CONF_DATA3_PIN = "data3_pin"
CONF_MODE_1BIT = "mode_1bit"
CONF_POWER_PIN = "power_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCard),
    cv.Optional(CONF_SD_CARD_ID): cv.declare_id(SDCard),
    cv.Required(CONF_CLK_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_CMD_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_DATA0_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_DATA1_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_DATA2_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_DATA3_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_MODE_1BIT, default=True): cv.boolean,
    cv.Required(CONF_POWER_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_SD_CARD_ID in config:
        cg.add(cg.Pvariable(config[CONF_SD_CARD_ID], var))

    clk = await cg.gpio_pin_expression(config[CONF_CLK_PIN])
    cg.add(var.set_clk_pin(clk))
    
    cmd = await cg.gpio_pin_expression(config[CONF_CMD_PIN])
    cg.add(var.set_cmd_pin(cmd))
    
    data0 = await cg.gpio_pin_expression(config[CONF_DATA0_PIN])
    cg.add(var.set_data0_pin(data0))
    
    power = await cg.gpio_pin_expression(config[CONF_POWER_PIN])
    cg.add(var.set_power_pin(power))
    
    cg.add(var.set_mode_1bit(config[CONF_MODE_1BIT]))

    if CONF_DATA1_PIN in config:
        data1 = await cg.gpio_pin_expression(config[CONF_DATA1_PIN])
        cg.add(var.set_data1_pin(data1))
    if CONF_DATA2_PIN in config:
        data2 = await cg.gpio_pin_expression(config[CONF_DATA2_PIN])
        cg.add(var.set_data2_pin(data2))
    if CONF_DATA3_PIN in config:
        data3 = await cg.gpio_pin_expression(config[CONF_DATA3_PIN])
        cg.add(var.set_data3_pin(data3))

