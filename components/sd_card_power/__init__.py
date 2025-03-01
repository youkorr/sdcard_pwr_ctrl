import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["esp32"]
AUTO_LOAD = ["sdcard"]

esp32s3box3_sd_card_ns = cg.esphome_ns.namespace("esp32s3box3_sd_card")
ESP32S3BOX3SDCard = esp32s3box3_sd_card_ns.class_("ESP32S3BOX3SDCard", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ESP32S3BOX3SDCard),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
