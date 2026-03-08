#include "theme.h"
// No display-library include needed — ThemeDef contains only colours and
// arc geometry. Fonts are handled by FONT_* macros in theme.h, which expand
// at the call site where M5Dial.h is already included.

// ════════════════════════════════════════════════════════════════════════════
//  Theme definitions
//
//  To add a new theme:
//    1. Add a new `const ThemeDef THEME_MY_NAME = { ... };` below.
//    2. Add a matching `else if` branch in LcdKnob::set_theme() (lcd_knob.cpp).
//    3. Add the name string to the `select:` options list in lcd-knob.yaml.
// ════════════════════════════════════════════════════════════════════════════

// ── Nordic Steel ─────────────────────────────────────────────────────────────
// B&O-inspired. Deep navy-black ground, steel-blue accent.
// Designed to read as continuous with a blue CNC-anodized frame.
const ThemeDef THEME_NORDIC_STEEL = {
  .bg       = 0x0883,  // #0C1018  deep navy-black
  .accent   = 0x7D79,  // #7AAFC8  steel blue
  .white    = 0xDF5E,  // #DDE8F0  cool white
  .grey_cc  = 0x7495,  // #7090A8  cool mid-slate
  .grey_55  = 0x2188,  // #243040  dark slate
  .grey_44  = 0x1906,  // #182030  very dark navy
  .grey_33  = 0x08C4,  // #0E1820  near-black navy
  .black    = 0x0000,  // #000000  art-overlay black

  .arc_start = 135, .arc_end_full = 405, .arc_sweep = 270.0f,
  .arc_outer = 105, .arc_inner = 97,
  .arc_vol_outer = 108, .arc_vol_inner = 96,
  .arc_deco_outer = 119, .arc_deco_inner = 117,
  .arc_cap_dist = 102.0f, .arc_cap_halo = 7, .arc_cap_dot = 5,
};

// ── Original Orange ───────────────────────────────────────────────────────────
// The original colour scheme. Warm charcoal ground, vivid orange accent.
const ThemeDef THEME_ORIGINAL_ORANGE = {
  .bg       = 0x18E3,  // #1A1A1A  warm charcoal
  .accent   = 0xFCA0,  // #FF9500  vivid orange
  .white    = 0xFFFF,  // #FFFFFF  pure white
  .grey_cc  = 0xCE79,  // #CCCCCC  light grey
  .grey_55  = 0x52AA,  // #555555  mid grey
  .grey_44  = 0x4228,  // #444444  dark grey
  .grey_33  = 0x31A6,  // #333333  near-black grey
  .black    = 0x0000,  // #000000  art-overlay black

  .arc_start = 135, .arc_end_full = 405, .arc_sweep = 270.0f,
  .arc_outer = 105, .arc_inner = 97,
  .arc_vol_outer = 108, .arc_vol_inner = 96,
  .arc_deco_outer = 119, .arc_deco_inner = 117,
  .arc_cap_dist = 102.0f, .arc_cap_halo = 7, .arc_cap_dot = 5,
};

// ── Active theme pointer ──────────────────────────────────────────────────────
// Default: Nordic Steel. Switched at runtime by LcdKnob::set_theme().
// Persists across screens; restored from NVS on boot via ESPHome select entity.
const ThemeDef* g_active_theme = &THEME_NORDIC_STEEL;
