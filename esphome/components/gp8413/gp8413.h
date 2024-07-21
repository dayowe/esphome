#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"

namespace esphome {
    namespace gp8413 {

        enum GP8413Voltage {
            GP8413_VOLTAGE_5V = 0x00,
            GP8413_VOLTAGE_10V = 0x11,
        };

        class GP8413 : public Component, public i2c::I2CDevice {
        public:
            void setup() override;
            void dump_config() override;
            float get_setup_priority() const override { return setup_priority::DATA; }

            void set_voltage(gp8413::GP8413Voltage voltage) { this->voltage_ = voltage; }

        protected:
            GP8413Voltage voltage_;
        };

    }  // namespace gp8413
}  // namespace esphome
