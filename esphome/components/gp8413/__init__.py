import esphome.config_validation as cv
import esphome.codegen as cg

from esphome.components import i2c
from esphome.const import CONF_ID, CONF_VOLTAGE

CODEOWNERS = ["@dayowe"]
DEPENDENCIES = ["i2c"]
MULTI_CONF = True

gp8413_ns = cg.esphome_ns.namespace("gp8413")
GP8413 = gp8413_ns.class_("GP8413", cg.Component, i2c.I2CDevice)

GP8413Voltage = gp8413_ns.enum("GP8413Voltage")

CONF_GP8413_ID = "gp8413_id"

VOLTAGES = {
    "5V": GP8413Voltage.GP8413_VOLTAGE_5V,
    "10V": GP8413Voltage.GP8413_VOLTAGE_10V,
}

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(GP8413),
            cv.Required(CONF_VOLTAGE): cv.enum(VOLTAGES, upper=True),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x59))  # Update I2C address here
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_voltage(config[CONF_VOLTAGE]))