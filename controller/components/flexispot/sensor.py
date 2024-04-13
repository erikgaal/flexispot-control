import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    CONF_OUTPUT_ID,
    UNIT_CENTIMETER,
    ICON_COUNTER,
    DEVICE_CLASS_DISTANCE,
    STATE_CLASS_MEASUREMENT,
)

CODEOWNERS = ["@erikgaal"]
DEPENDENCIES = ["uart"]

flexispot_ns = cg.esphome_ns.namespace("flexispot")
FlexispotComponent = flexispot_ns.class_("FlexispotComponent", sensor.Sensor, cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        FlexispotComponent,
        unit_of_measurement=UNIT_CENTIMETER,
        icon=ICON_COUNTER,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_DISTANCE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend({
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(FlexispotComponent),
    })
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
