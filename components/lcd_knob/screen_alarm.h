#pragma once

#include "screen.h"
#include <cstdint>

namespace esphome {
namespace lcd_knob {

enum class AlarmEditField : uint8_t { NONE, HOUR, MINUTE };

// ── Alarm state ───────────────────────────────────────────────────────────────
struct AlarmState {
  uint8_t       hour{7};
  uint8_t       minute{0};
  bool          armed{false};
  bool          fired{false};
  AlarmEditField edit_field{AlarmEditField::NONE};
};

// ── Alarm screen ──────────────────────────────────────────────────────────────
//
// Short press cycles: NONE → HOUR → MINUTE → (save + arm) → NONE
// Rotary adjusts the currently-edited field.
// Long press:  disarms / cancels edit; returns true.
// check(h,m):  call from LcdKnob::check_alarms() every minute.
class AlarmScreen : public Screen {
 public:
  explicit AlarmScreen(const char *label, AlarmState *state)
      : label_(label), state_(state) {}

  void draw()           override;
  void on_rotary_cw()   override;
  void on_rotary_ccw()  override;
  void on_short_press() override;
  bool on_long_press()  override;

  void check(uint8_t h, uint8_t m);

 private:
  const char *label_;
  AlarmState *state_;

  uint32_t blink_ms_{0};
  bool     blink_on_{true};
};

}  // namespace lcd_knob
}  // namespace esphome
