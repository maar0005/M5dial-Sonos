#pragma once

#include "screen.h"
#include <cstdint>

namespace esphome {
namespace lcd_knob {

// ── Countdown timer state ──────────────────────────────────────────────────────
struct TimerState {
  uint32_t duration_s{300};      // settable duration (default 5 min)
  uint32_t remaining_s{300};     // countdown value currently shown
  uint32_t start_ms{0};          // millis() when last started/resumed
  uint32_t elapsed_at_pause{0};  // seconds elapsed before the last pause
  bool     running{false};
  bool     fired{false};         // latched true when countdown reaches 0
};

// ── Countdown timer screen ────────────────────────────────────────────────────
//
// Rotary (when stopped):  CW = +30 s, CCW = −30 s, with acceleration.
// Short press:            start / pause toggle.
// Long press:             reset; returns true (consumes the long press).
// tick(now_ms):           call from LcdKnob::loop() every iteration.
class TimerScreen : public Screen {
 public:
  explicit TimerScreen(const char *label, TimerState *state)
      : label_(label), state_(state) {}

  void draw()           override;
  void on_rotary_cw()   override;
  void on_rotary_ccw()  override;
  void on_short_press() override;
  bool on_long_press()  override;

  void tick(uint32_t now_ms);

 private:
  const char  *label_;
  TimerState  *state_;

  // Rotary acceleration
  uint32_t last_rotary_ms_{0};
  int      rotary_streak_{0};

  void adjust_duration(int direction);
};

}  // namespace lcd_knob
}  // namespace esphome
