#pragma once

#include "screen.h"
#include <string>

namespace esphome {
namespace m5dial_sonos {

// ── Meater+ probe temperature screen ─────────────────────────────────────────
//
// Displays internal probe temperature and progress arc toward the target.
// Optional ambient temperature shown below.
//
// YAML config example:
//   - type: meater
//     used: true
//     entity_temperature: sensor.meater_probe_1_internal_temperature
//     entity_target:      sensor.meater_probe_1_target_temperature
//     entity_ambient:     sensor.meater_probe_1_ambient_temperature
//
// In text_sensor / sensor subscriptions call:
//   id(sonos_ui).set_meater_temperature(x);
//   id(sonos_ui).set_meater_target(x);
//   id(sonos_ui).set_meater_ambient(x);

class MeaterScreen : public Screen {
 public:
  // Config setters — called from generated code
  void set_entity_temperature(const std::string &e) { entity_temp_    = e; }
  void set_entity_target     (const std::string &e) { entity_target_  = e; }
  void set_entity_ambient    (const std::string &e) { entity_ambient_ = e; }

  // State setters — called from YAML sensor lambdas
  void set_temperature(float t) { temp_     = t; has_temp_   = true; mark_dirty(); }
  void set_target     (float t) { target_   = t; has_target_ = true; mark_dirty(); }
  void set_ambient    (float t) { ambient_  = t;                      mark_dirty(); }

  void draw() override;

 private:
  std::string entity_temp_, entity_target_, entity_ambient_;

  float temp_   {0.0f};
  float target_ {0.0f};
  float ambient_{0.0f};
  bool  has_temp_  {false};
  bool  has_target_{false};
};

}  // namespace m5dial_sonos
}  // namespace esphome
