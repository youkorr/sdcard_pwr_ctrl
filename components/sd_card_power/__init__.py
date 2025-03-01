import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CLK_PIN, CONF_CMD_PIN, CONF_DATA0_PIN, CONF_DATA1_PIN, CONF_DATA2_PIN, CONF_DATA3_PIN
from esphome import pins
from esphome.components import sd_mmc_card
from esphome.const import (
    CONF_ID,
    CONF_CLK_PIN,
    CONF_CMD_PIN,
    CONF_DATA0_PIN,
    CONF_DATA1_PIN,
    CONF_DATA2_PIN,
    CONF_DATA3_PIN,
    CONF_MODE,
)

DEPENDENCIES = ["esp32"]
AUTO_LOAD = ["sd_mmc_card"]


sd_card_ns = cg.esphome_ns.namespace("sd_card_power")
SDCard = sd_card_ns.class_("SDCard", cg.Component)

CONF_SD_MMC_CARD_ID = "sd_mmc_card_id"
CONF_MODE_1BIT = "mode_1bit"
CONF_POWER_PIN = "power_pin"
CONF_CMD_PIN = "cmd_pin"
CONF_DATA0_PIN = "data0_pin"
CONF_DATA1_PIN = "data1_pin"
CONF_DATA2_PIN = "data2_pin"
CONF_DATA3_PIN = "data3_pin"


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCard),
    cv.GenerateID(CONF_SD_MMC_CARD_ID): cv.use_id(sd_mmc_card.SdMmc),
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

    cg.add(var.set_power_pin(config[CONF_POWER_PIN]))

    # Configure SD MMC Card
    sd_mmc_config = {
        CONF_CLK_PIN: config[CONF_CLK_PIN],
        CONF_CMD_PIN: config[CONF_CMD_PIN],
        CONF_DATA0_PIN: config[CONF_DATA0_PIN],
        CONF_MODE_1BIT: config[CONF_MODE_1BIT],
    }
    if CONF_DATA1_PIN in config:
        sd_mmc_config[CONF_DATA1_PIN] = config[CONF_DATA1_PIN]
    if CONF_DATA2_PIN in config:
        sd_mmc_config[CONF_DATA2_PIN] = config[CONF_DATA2_PIN]
    if CONF_DATA3_PIN in config:
        sd_mmc_config[CONF_DATA3_PIN] = config[CONF_DATA3_PIN]

    sd_mmc_var = await sd_mmc_card.new_sd_mmc_card(sd_mmc_config)
    cg.add(var.set_sd_mmc_card(sd_mmc_var))
