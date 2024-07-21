#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
  namespace m5stack_dac2 {

    enum GP8413Voltage {
      GP8413_VOLTAGE_5V,
      GP8413_VOLTAGE_10V,
    };

    class GP8413 : public Component, public i2c::I2CDevice {
    public:
      void setup() override;
      void dump_config() override;
      void set_voltage(GP8413Voltage voltage) { this->voltage_ = voltage; }
      void write_register(uint8_t reg, uint8_t *data, uint8_t len);

    protected:
      GP8413Voltage voltage_;
    };

  }  // namespace m5stack_dac2
}  // namespace esphome
