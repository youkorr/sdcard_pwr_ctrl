import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_CLK_PIN,
    CONF_CMD_PIN,
    CONF_DATA0_PIN,
    CONF_DATA1_PIN,
    CONF_DATA2_PIN,
    CONF_DATA3_PIN,
)

DEPENDENCIES = ["esp32"]

sd_card_ns = cg.esphome_ns.namespace("sd_card")
SDCard = sd_card_ns.class_("SDCard", cg.Component)

CONF_MODE_1BIT = "mode_1bit"
CONF_POWER_PIN = "power_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCard),
    cv.Required(CONF_CLK_PIN): pins.internal_gpio_output_pin_number,
    cv.Required(CONF_CMD_PIN): pins.internal_gpio_output_pin_number,
    cv.Required(CONF_DATA0_PIN): pins.internal_gpio_pin_number,
    cv.Optional(CONF_DATA1_PIN): pins.internal_gpio_pin_number,
    cv.Optional(CONF_DATA2_PIN): pins.internal_gpio_pin_number,
    cv.Optional(CONF_DATA3_PIN): pins.internal_gpio_pin_number,
    cv.Optional(CONF_MODE_1BIT, default=True): cv.boolean,
    cv.Required(CONF_POWER_PIN): pins.internal_gpio_output_pin_number,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_clk_pin(config[CONF_CLK_PIN]))
    cg.add(var.set_cmd_pin(config[CONF_CMD_PIN]))
    cg.add(var.set_data0_pin(config[CONF_DATA0_PIN]))
    cg.add(var.set_power_pin(config[CONF_POWER_PIN]))
    cg.add(var.set_mode_1bit(config[CONF_MODE_1BIT]))

    if CONF_DATA1_PIN in config:
        cg.add(var.set_data1_pin(config[CONF_DATA1_PIN]))
    if CONF_DATA2_PIN in config:
        cg.add(var.set_data2_pin(config[CONF_DATA2_PIN]))
    if CONF_DATA3_PIN in config:
        cg.add(var.set_data3_pin(config[CONF_DATA3_PIN]))

