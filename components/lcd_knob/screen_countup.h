#pragma once

#include "screen.h"
#include <cstdint>

namespace esphome {
namespace lcd_knob {

// ── Count-up timer state ──────────────────────────────────────────────────────
struct CountUpState {
  uint32_t start_ms{0};
  bool     running{false};
  uint32_t elapsed_s{0};
};

// ── Count-up timer screen ─────────────────────────────────────────────────────
//
// Short press:  start (if not running).
// Long press:   reset to 0; returns true.
// tick(now_ms): call from LcdKnob::loop() every iteration.
class CountUpScreen : public Screen {
 public:
  explicit CountUpScreen(CountUpState *state) : state_(state) {}

  void draw()           override;
  void on_short_press() override;

  void tick(uint32_t now_ms);

 private:
  CountUpState *state_;
  uint32_t      last_elapsed_s_{0xFFFFFFFF};
};

}  // namespace lcd_knob
}  // namespace esphome
