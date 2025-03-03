import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PIN
import esphome.components.esp32 as esp32

CONF_POWER_CTRL_PIN = 'power_ctrl_pin'
DEPENDENCIES = ['esp32']

sdmmc_card_ns = cg.esphome_ns.namespace('sd_mmc_card')
SdMmc = sdmmc_card_ns.class_('SdMmc', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SdMmc),
    cv.Optional(CONF_POWER_CTRL_PIN): cv.gpio_pin,
    # Autres options existantes de configuration
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    # Ajout de la configuration du pin de contrôle de puissance
    if CONF_POWER_CTRL_PIN in config:
        pin = config[CONF_POWER_CTRL_PIN]
        cg.add(var.set_power_ctrl_pin(pin))
    
    yield cg.register_component(var, config)




