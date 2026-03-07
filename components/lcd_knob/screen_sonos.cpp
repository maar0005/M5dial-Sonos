#include "screen_sonos.h"
#include <M5Dial.h>

namespace esphome {
namespace lcd_knob {

// ═══════════════════════════════════════════════════════════════════════════════
// SonosPlaylistScreen
// ═══════════════════════════════════════════════════════════════════════════════

void SonosPlaylistScreen::on_rotary_cw() {
  if (state_->playlist_names.empty()) return;
  int n = state_->playlist_names.size();
  state_->playlist_index = (state_->playlist_index + 1) % n;
  mark_dirty();
}

void SonosPlaylistScreen::on_rotary_ccw() {
  if (state_->playlist_names.empty()) return;
  int n = state_->playlist_names.size();
  state_->playlist_index = (state_->playlist_index - 1 + n) % n;
  mark_dirty();
}

void SonosPlaylistScreen::draw() {
  auto &dsp = M5Dial.Display;
  dsp.fillScreen(COL_BG);

  // Music note icon header
  dsp.setTextColor(COL_ORANGE, COL_BG);
  dsp.setTextDatum(middle_center);
  dsp.setFont(&fonts::FreeSansBold18pt7b);
  dsp.drawString("~", CENTER_X, 32);

  if (state_->playlist_names.empty()) {
    dsp.setFont(&fonts::FreeSansBold12pt7b);
    dsp.setTextColor(COL_WHITE, COL_BG);
    dsp.drawString("No favourites", CENTER_X, CENTER_Y);
    return;
  }

  int n    = state_->playlist_names.size();
  int prev = (state_->playlist_index - 1 + n) % n;
  int next = (state_->playlist_index + 1) % n;

  screen_draw_clipped(CENTER_X, CENTER_Y - 44,
                      state_->playlist_names[prev], 160,
                      COL_GREY_55, &fonts::FreeSansBold9pt7b);

  screen_draw_clipped(CENTER_X, CENTER_Y,
                      state_->playlist_names[state_->playlist_index], 200,
                      COL_WHITE, &fonts::FreeSansBold12pt7b);

  screen_draw_clipped(CENTER_X, CENTER_Y + 44,
                      state_->playlist_names[next], 160,
                      COL_GREY_55, &fonts::FreeSansBold9pt7b);
}

// ═══════════════════════════════════════════════════════════════════════════════
// SonosNowPlayingScreen
// ═══════════════════════════════════════════════════════════════════════════════

void SonosNowPlayingScreen::draw() {
  auto &dsp = M5Dial.Display;
  dsp.fillScreen(COL_BG);

  // Play/pause icon
  if (state_->is_playing) {
    dsp.fillRect(CENTER_X - 10, 18, 6, 20, COL_ORANGE);
    dsp.fillRect(CENTER_X + 4,  18, 6, 20, COL_ORANGE);
  } else {
    dsp.fillTriangle(CENTER_X - 8, 18, CENTER_X - 8, 38,
                     CENTER_X + 10, 28, COL_ORANGE);
  }

  screen_draw_clipped(CENTER_X, CENTER_Y - 10,
                      state_->media_title, 200,
                      COL_WHITE, &fonts::FreeSansBold12pt7b);

  screen_draw_clipped(CENTER_X, CENTER_Y + 24,
                      state_->media_artist, 200,
                      COL_GREY_CC, &fonts::FreeSansBold9pt7b);
}

// ═══════════════════════════════════════════════════════════════════════════════
// SonosVolumeScreen
// ═══════════════════════════════════════════════════════════════════════════════

void SonosVolumeScreen::on_rotary_cw() {
  float step = volume_step_ / 100.0f;
  state_->volume += step;
  if (state_->volume > 1.0f) state_->volume = 1.0f;
  mark_dirty();
}

void SonosVolumeScreen::on_rotary_ccw() {
  float step = volume_step_ / 100.0f;
  state_->volume -= step;
  if (state_->volume < 0.0f) state_->volume = 0.0f;
  mark_dirty();
}

void SonosVolumeScreen::draw() {
  auto &dsp = M5Dial.Display;
  dsp.fillScreen(COL_BG);

  // Header
  dsp.setTextColor(COL_ORANGE, COL_BG);
  dsp.setTextDatum(middle_center);
  dsp.setFont(&fonts::FreeSansBold9pt7b);
  dsp.drawString("Volume", CENTER_X, 32);

  int pct = static_cast<int>(state_->volume * 100.0f + 0.5f);

  // Background arc (270°, gap at bottom, 135° → 405°)
  dsp.fillArc(CENTER_X, CENTER_Y, 105, 97, 135, 405, COL_GREY_33);

  // Foreground arc (filled to percentage)
  if (pct > 0) {
    float end_angle = 135.0f + 270.0f * pct / 100.0f;
    dsp.fillArc(CENTER_X, CENTER_Y, 105, 97, 135, static_cast<int>(end_angle), COL_ORANGE);
  }

  // Percentage text
  char buf[8];
  snprintf(buf, sizeof(buf), "%d%%", pct);
  dsp.setTextColor(COL_WHITE, COL_BG);
  dsp.setFont(&fonts::FreeSansBold18pt7b);
  dsp.drawString(buf, CENTER_X, CENTER_Y);
}

}  // namespace lcd_knob
}  // namespace esphome
