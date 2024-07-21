#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/components/m5stack_dac2/gp8413.h"

namespace esphome {
  namespace m5stack_dac2 {

    class GP8413Output : public Component, public output::FloatOutput, public Parented<esphome::m5stack_dac2::GP8413> {
    public:
      void dump_config() override;
      float get_setup_priority() const override { return setup_priority::DATA - 1; }

      void set_channel(uint8_t channel) { this->channel_ = channel; }

      void write_state(float state) override;

    protected:
      uint8_t channel_;
    };

  }  // namespace m5stack_dac2
}  // namespace esphome
