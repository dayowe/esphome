#include "gp8413_output.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace gp8413 {

        static const char* const TAG = "gp8413.output";

        static const uint8_t OUTPUT_REGISTER = 0x02;

        void GP8413Output::dump_config() {
            ESP_LOGCONFIG(TAG, "GP8413 Output:");
            ESP_LOGCONFIG(TAG, "  Channel: %u", this->channel_);
        }

        void GP8413Output::write_state(float state) {
            uint16_t value = (uint16_t)(state * 32767);
            i2c::ErrorCode err = this->parent_->write_register(OUTPUT_REGISTER + (2 * this->channel_), (uint8_t*)&value, 2);
            if (err != i2c::ERROR_OK) {
                ESP_LOGE(TAG, "Error writing to GP8413, code %d", err);
            }
        }

    }  // namespace gp8413
}  // namespace esphome
