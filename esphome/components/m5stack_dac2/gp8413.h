#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
  namespace m5stack_dac2 {

    class GP8413 : public Component, public i2c::I2CDevice {
    public:
      void set_voltage(float voltage);
      void write_register(uint8_t reg, uint8_t *data, uint8_t len);

      // Other necessary member functions and variables
    };

  }  // namespace m5stack_dac2
}  // namespace esphome
