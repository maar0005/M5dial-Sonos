#pragma once

#include "screen.h"
#include <string>
#include <vector>

namespace esphome {
namespace lcd_knob {

// ── Shared Sonos playback state ───────────────────────────────────────────────
// Owned by LcdKnob. All three Sonos screens hold a pointer to this.
struct SonosState {
  std::string entity;
  std::vector<std::string> playlist_names;
  int         playlist_index{0};
  float       volume{0.0f};
  bool        is_playing{false};
  std::string media_title{"—"};
  std::string media_artist;
};

// ── Playlist browser ──────────────────────────────────────────────────────────
class SonosPlaylistScreen : public Screen {
 public:
  explicit SonosPlaylistScreen(SonosState *state) : state_(state) {}

  void draw() override;
  void on_rotary_cw()  override;
  void on_rotary_ccw() override;

 private:
  SonosState *state_;
};

// ── Now playing ───────────────────────────────────────────────────────────────
class SonosNowPlayingScreen : public Screen {
 public:
  explicit SonosNowPlayingScreen(SonosState *state) : state_(state) {}

  void draw() override;

 private:
  SonosState *state_;
};

// ── Volume control ────────────────────────────────────────────────────────────
class SonosVolumeScreen : public Screen {
 public:
  SonosVolumeScreen(SonosState *state, int volume_step)
      : state_(state), volume_step_(volume_step) {}

  void draw() override;
  void on_rotary_cw()  override;
  void on_rotary_ccw() override;

  int volume_step() const { return volume_step_; }

 private:
  SonosState *state_;
  int         volume_step_;
};

}  // namespace lcd_knob
}  // namespace esphome
