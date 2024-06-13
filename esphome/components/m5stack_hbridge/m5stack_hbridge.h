#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5stack_hbridge {

enum hbridge_direction_t {
  HBRIDGE_STOP = 0,
  HBRIDGE_FORWARD,
  HBRIDGE_BACKWARD
};

enum hbridge_analog_read_mode_t {
  _8bit = 0,
  _12bit
};

class M5StackHBridge : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void loop() override;
  void set_direction(hbridge_direction_t direction);
  void set_speed8bits(uint8_t speed);
  void set_speed16bits(uint16_t speed);
  void set_pwm_freq(uint16_t freq);
  uint8_t get_direction();
  uint8_t get_speed8bits();
  uint16_t get_speed16bits();
  uint16_t get_pwm_freq();
  uint16_t get_analog_input(hbridge_analog_read_mode_t bit);
  float get_motor_current();
  uint8_t get_firmware_version();
  uint8_t get_i2c_address();
  void jump_bootloader();

  void set_i2c_pins(uint8_t sda, uint8_t scl);
  void set_i2c_speed(uint32_t speed);

 private:
  void write_bytes(uint8_t reg, uint8_t *buffer, uint8_t length);
  void read_bytes(uint8_t reg, uint8_t *buffer, uint8_t length);

  uint8_t sda_;
  uint8_t scl_;
  uint32_t i2c_speed_;
};

}  // namespace m5stack_hbridge
}  // namespace esphome
