#include "m5stack_hbridge.h"
#include "esphome/core/log.h"
#include "Wire.h"

namespace esphome {
namespace m5stack_hbridge {

static const char *TAG = "m5stack_hbridge";

// Register addresses
#define HBRIDGE_CONFIG_REG             0x00
#define HBRIDGE_MOTOR_ADC_8BIT_REG     0x10
#define HBRIDGE_MOTOR_ADC_12BIT_REG    0x20
#define HBRIDGE_MOTOR_CURRENT_REG      0x30
#define HBRIDGE_JUMP_TO_BOOTLOADER_REG 0xFD
#define HBRIDGE_FW_VERSION_REG         0xFE
#define HBRIDGE_I2C_ADDRESS_REG        0xFF

void M5StackHBridge::setup() {
  ESP_LOGD(TAG, "Setting up M5Stack HBridge...");
  Wire.begin(this->sda_, this->scl_);
  Wire.setClock(this->i2c_speed_);

  // Test I2C Communication with the HBridge
  uint8_t version = this->get_firmware_version();
  ESP_LOGD(TAG, "HBridge Firmware Version: %d", version);
}

void M5StackHBridge::loop() {
  // Implement loop logic if necessary
}

void M5StackHBridge::set_direction(hbridge_direction_t direction) {
  ESP_LOGD(TAG, "Setting direction: %d", direction);
  uint8_t data[1] = { static_cast<uint8_t>(direction) };
  this->write_bytes(HBRIDGE_CONFIG_REG, data, 1);
}

void M5StackHBridge::set_speed8bits(uint8_t speed) {
  ESP_LOGD(TAG, "Setting 8-bit speed: %d", speed);
  uint8_t data[1] = { speed };
  this->write_bytes(HBRIDGE_CONFIG_REG + 1, data, 1);
}

void M5StackHBridge::set_speed16bits(uint16_t speed) {
  ESP_LOGD(TAG, "Setting 16-bit speed: %d", speed);
  uint8_t data[2] = { static_cast<uint8_t>(speed & 0xFF), static_cast<uint8_t>((speed >> 8) & 0xFF) };
  this->write_bytes(HBRIDGE_CONFIG_REG + 2, data, 2);
}

void M5StackHBridge::set_pwm_freq(uint16_t freq) {
  ESP_LOGD(TAG, "Setting PWM frequency: %d", freq);
  uint8_t data[2] = { static_cast<uint8_t>(freq & 0xFF), static_cast<uint8_t>((freq >> 8) & 0xFF) };
  this->write_bytes(HBRIDGE_CONFIG_REG + 4, data, 2);
}

uint8_t M5StackHBridge::get_direction() {
  uint8_t data[1];
  this->read_bytes(HBRIDGE_CONFIG_REG, data, 1);
  return data[0];
}

uint8_t M5StackHBridge::get_speed8bits() {
  uint8_t data[1];
  this->read_bytes(HBRIDGE_CONFIG_REG + 1, data, 1);
  return data[0];
}

uint16_t M5StackHBridge::get_speed16bits() {
  uint8_t data[2];
  this->read_bytes(HBRIDGE_CONFIG_REG + 2, data, 2);
  return (data[0] | (data[1] << 8));
}

uint16_t M5StackHBridge::get_pwm_freq() {
  uint8_t data[2];
  this->read_bytes(HBRIDGE_CONFIG_REG + 4, data, 2);
  return (data[0] | (data[1] << 8));
}

uint16_t M5StackHBridge::get_analog_input(hbridge_analog_read_mode_t bit) {
  uint8_t reg = (bit == _8bit) ? HBRIDGE_MOTOR_ADC_8BIT_REG : HBRIDGE_MOTOR_ADC_12BIT_REG;
  uint8_t data[2];
  this->read_bytes(reg, data, (bit == _8bit) ? 1 : 2);
  return (bit == _8bit) ? data[0] : (data[0] | (data[1] << 8));
}

float M5StackHBridge::get_motor_current() {
  uint8_t data[4];
  this->read_bytes(HBRIDGE_MOTOR_CURRENT_REG, data, 4);
  float current;
  memcpy(&current, data, sizeof(current));
  return current;
}

uint8_t M5StackHBridge::get_firmware_version() {
  uint8_t data[1];
  this->read_bytes(HBRIDGE_FW_VERSION_REG, data, 1);
  return data[0];
}

uint8_t M5StackHBridge::get_i2c_address() {
  uint8_t data[1];
  this->read_bytes(HBRIDGE_I2C_ADDRESS_REG, data, 1);
  return data[0];
}

void M5StackHBridge::jump_bootloader() {
  uint8_t value = 1;
  this->write_bytes(HBRIDGE_JUMP_TO_BOOTLOADER_REG, &value, 1);
}

void M5StackHBridge::write_bytes(uint8_t reg, uint8_t *buffer, uint8_t length) {
  Wire.beginTransmission(this->address_);
  Wire.write(reg);
  for (uint8_t i = 0; i < length; i++) {
    Wire.write(buffer[i]);
  }
  uint8_t result = Wire.endTransmission();
  if (result != 0) {
    ESP_LOGE(TAG, "Error %d when writing bytes", result);
  }
}

void M5StackHBridge::read_bytes(uint8_t reg, uint8_t *buffer, uint8_t length) {
  Wire.beginTransmission(this->address_);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(static_cast<uint8_t>(this->address_), static_cast<uint8_t>(length));
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
}

void M5StackHBridge::set_i2c_pins(uint8_t sda, uint8_t scl) {
  this->sda_ = sda;
  this->scl_ = scl;
  ESP_LOGD(TAG, "Setting I2C pins: SDA=%d, SCL=%d", sda, scl);
}

void M5StackHBridge::set_i2c_speed(uint32_t speed) {
  this->i2c_speed_ = speed;
  ESP_LOGD(TAG, "Setting I2C speed: %d", speed);
}

}  // namespace m5stack_hbridge
}  // namespace esphome
