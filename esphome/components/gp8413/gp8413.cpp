#include "gp8413.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace gp8413 {

        static const char* const TAG = "gp8413";

        static const uint8_t RANGE_REGISTER = 0x01;

        void GP8413::setup() {
            ESP_LOGD(TAG, "Setting up GP8413 with voltage: %dV", this->voltage_ == GP8413_VOLTAGE_5V ? 5 : 10);
            i2c::ErrorCode err = this->write_register(RANGE_REGISTER, (uint8_t*)(&this->voltage_), 1);
            if (err != i2c::ERROR_OK) {
                ESP_LOGE(TAG, "Error setting up GP8413, code %d", err);
            } else {
                ESP_LOGD(TAG, "Successfully set up GP8413 with voltage: %dV", this->voltage_ == GP8413_VOLTAGE_5V ? 5 : 10);
            }
        }

        void GP8413::dump_config() {
            ESP_LOGCONFIG(TAG, "GP8413:");
            ESP_LOGCONFIG(TAG, "  Voltage: %dV", this->voltage_ == GP8413_VOLTAGE_5V ? 5 : 10);
            LOG_I2C_DEVICE(this);
        }

    }  // namespace gp8413
}  // namespace esphome
