import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_ID, CONF_PIN

DEPENDENCIES = []
CODEOWNERS = ["@votre-nom-utilisateur"]

sd_card_power_ns = cg.esphome_ns.namespace("sd_card_power")
SDCardPower = sd_card_power_ns.class_("SDCardPower", cg.Component)

CONF_POWER_ON_BOOT = "power_on_boot"
CONF_INVERTED = "inverted"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SDCardPower),
    cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_POWER_ON_BOOT, default=True): cv.boolean,
    cv.Optional(CONF_INVERTED, default=False): cv.boolean,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_power_pin(pin))
    
    if CONF_POWER_ON_BOOT in config:
        cg.add(var.set_power_on_boot(config[CONF_POWER_ON_BOOT]))
        
    if CONF_INVERTED in config:
        cg.add(var.set_inverted(config[CONF_INVERTED]))
