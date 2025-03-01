import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import sd_mmc_card

DEPENDENCIES = ["esp32", "sd_mmc_card"]

esp32s3box3_sd_card_ns = cg.esphome_ns.namespace("esp32s3box3_sd_card")
ESP32S3BOX3SDCard = esp32s3box3_sd_card_ns.class_("ESP32S3BOX3SDCard", cg.Component)

CONF_SD_MMC_CARD_ID = "sd_mmc_card_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ESP32S3BOX3SDCard),
    cv.Required(CONF_SD_MMC_CARD_ID): cv.use_id(sd_mmc_card.SdMmc),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    sd_mmc = await cg.get_variable(config[CONF_SD_MMC_CARD_ID])
    cg.add(var.set_sd_mmc_card(sd_mmc))
