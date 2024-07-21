#include "gp8413_output.h"
#include "esphome/core/log.h"

namespace esphome {
  namespace gp8413 {

    static const char *TAG = "gp8413.output";

    static const uint8_t OUTPUT_REGISTER = 0x02;

    void GP8413Output::dump_config() {
      ESP_LOGCONFIG(TAG, "GP8413 Output:");
      ESP_LOGCONFIG(TAG, "  Channel: %u", this->channel_);
    }

    void GP8413Output::write_state(float state) {
      uint16_t value = state * 0x7FFF;
      uint8_t data[2];
      data[0] = (value >> 8) & 0x7F;  // High byte
      data[1] = value & 0xFF;         // Low byte
      
      i2c::ErrorCode err = this->parent_->write_register(OUTPUT_REGISTER + (2 * this->channel_), data, 2);
      if (err != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "Error writing to GP8413, code %d", err);
      }
    }

  }  // namespace gp8413
}  // namespace esphome
