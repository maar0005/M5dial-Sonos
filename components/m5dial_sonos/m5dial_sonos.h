#pragma once

#include "esphome/core/component.h"
#include "screen.h"
#include "screen_sonos.h"
#include "screen_meater.h"
#include <vector>
#include <string>

namespace esphome {
namespace m5dial_sonos {

// ── Screen type tags (for ScreenKind ordering) ────────────────────────────────
enum class ScreenKind : uint8_t { SONOS, MEATER };

struct ScreenConfig {
  ScreenKind kind;
  // Sonos
  std::string sonos_entity;
  int         sonos_volume_step{2};
  // Meater
  std::string meater_entity_temp;
  std::string meater_entity_target;
  std::string meater_entity_ambient;
};

class M5DialSonos : public Component {
 public:
  // ── ESPHome lifecycle ──────────────────────────────────────────────────────
  void setup() override;
  void loop()  override;
  float get_setup_priority() const override;

  // ── Global config ──────────────────────────────────────────────────────────
  void set_screen_off_time   (uint32_t ms) { screen_off_time_    = ms; }
  void set_long_press_duration(uint32_t ms) { long_press_duration_ = ms; }

  // ── Screen declarations (called in order from generated code) ─────────────
  // Adds three Sonos screens (Playlist, NowPlaying, Volume) to the list.
  void configure_sonos(const std::string &entity, int volume_step);
  // Adds one Meater screen. Empty strings for unused entities.
  void configure_meater(const std::string &entity_temp,
                        const std::string &entity_target,
                        const std::string &entity_ambient);

  // ── Sonos state setters — called from YAML text_sensor lambdas ────────────
  void set_playlist_json (const std::string &json);
  void set_media_title   (const std::string &title);
  void set_media_artist  (const std::string &artist);
  void set_volume_level  (float level);
  void set_player_state  (const std::string &state);

  // ── Sonos getters — used by YAML action scripts ───────────────────────────
  float       get_volume()               const;
  int         get_playlist_count()       const;
  std::string get_current_playlist_name() const;

  // ── Screen-type queries — for YAML action dispatching ─────────────────────
  bool is_sonos_playlist()   const;
  bool is_sonos_now_playing() const;
  bool is_sonos_volume()     const;
  bool is_meater()           const;

  // ── Meater state setters — called from YAML sensor lambdas ───────────────
  void set_meater_temperature(float t);
  void set_meater_target     (float t);
  void set_meater_ambient    (float t);

  // ── Input handlers — called from YAML rotary / button lambdas ────────────
  void on_rotary_cw();
  void on_rotary_ccw();
  void on_short_press();
  void on_long_press();
  void wake_screen();

 private:
  // ── Config queue (populated before setup()) ────────────────────────────────
  std::vector<ScreenConfig> screen_configs_;

  // ── Runtime ────────────────────────────────────────────────────────────────
  std::vector<Screen *> screens_;
  size_t current_{0};

  // Typed pointers for state forwarding (null if not configured)
  SonosState          sonos_state_;
  SonosPlaylistScreen   *sonos_playlist_  {nullptr};
  SonosNowPlayingScreen *sonos_now_playing_{nullptr};
  SonosVolumeScreen     *sonos_volume_    {nullptr};
  MeaterScreen          *meater_          {nullptr};

  // ── Display state ──────────────────────────────────────────────────────────
  uint32_t screen_off_time_    {30000};
  uint32_t long_press_duration_{800};
  uint32_t last_interaction_   {0};
  bool     screen_dimmed_      {false};

  static constexpr uint8_t BRIGHTNESS_FULL = 100;
  static constexpr uint8_t BRIGHTNESS_DIM  = 25;

  void next_screen();
  void draw_mode_dots();
};

}  // namespace m5dial_sonos
}  // namespace esphome
