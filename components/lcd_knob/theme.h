#pragma once
#include <cstdint>

// ════════════════════════════════════════════════════════════════════════════
//  THEME — runtime-switchable design system
//
//  All visual design decisions live here. To restyle the entire UI, either:
//    • Change g_active_theme at runtime (via set_theme() / HA dropdown), or
//    • Edit a ThemeDef instance in theme.cpp, or
//    • Add a new ThemeDef in theme.cpp and extend set_theme().
//
//  Screen .cpp files use COL_*, FONT_*, ARC_* directly — no changes needed
//  there when adding or switching themes.
// ════════════════════════════════════════════════════════════════════════════

// ── Theme definition struct ───────────────────────────────────────────────────
// Fonts are NOT part of ThemeDef — they are the same across all themes.
// See FONT_* macros below.
struct ThemeDef {
  // Colour palette (RGB565)
  uint16_t bg;       // background
  uint16_t accent;   // primary accent / interactive colour
  uint16_t white;    // primary text
  uint16_t grey_cc;  // secondary text
  uint16_t grey_55;  // muted / inactive text
  uint16_t grey_44;  // dividers, subtle hints
  uint16_t grey_33;  // arc track background
  uint16_t black;    // art-overlay / pure black

  // Arc geometry
  int   arc_start;       // start angle (degrees)
  int   arc_end_full;    // arc_start + 270 (full sweep)
  float arc_sweep;       // total sweep in degrees (270.0)
  int   arc_outer;       // standard ring outer radius
  int   arc_inner;       // standard ring inner radius
  int   arc_vol_outer;   // volume ring outer radius
  int   arc_vol_inner;   // volume ring inner radius
  int   arc_deco_outer;  // Sonos decorative ring outer
  int   arc_deco_inner;  // Sonos decorative ring inner
  float arc_cap_dist;    // distance from center to cap-dot center
  int   arc_cap_halo;    // cap-dot dark halo radius
  int   arc_cap_dot;     // cap-dot bright tip radius
};

// ── Active theme pointer — switched at runtime ────────────────────────────────
// Defined in theme.cpp; default = THEME_NORDIC_STEEL.
// All COL_* and ARC_* macros below dereference this pointer.
extern const ThemeDef* g_active_theme;

// ── Colour macros ─────────────────────────────────────────────────────────────
#define COL_BG       (g_active_theme->bg)
#define COL_ACCENT   (g_active_theme->accent)
#define COL_ORANGE   (g_active_theme->accent)   // legacy alias — keeps existing code unchanged
#define COL_WHITE    (g_active_theme->white)
#define COL_GREY_CC  (g_active_theme->grey_cc)
#define COL_GREY_55  (g_active_theme->grey_55)
#define COL_GREY_44  (g_active_theme->grey_44)
#define COL_GREY_33  (g_active_theme->grey_33)
#define COL_BLACK    (g_active_theme->black)

// ── Typography macros ─────────────────────────────────────────────────────────
// Fonts are the same across all themes — defined as simple macros here.
// They expand at the call site (in screen .cpp files) where M5Dial.h is
// already included, so no display-library include is needed in theme.h.
#define FONT_SMALL   (&fonts::FreeSansBold9pt7b)
#define FONT_MEDIUM  (&fonts::FreeSansBold12pt7b)
#define FONT_LARGE   (&fonts::FreeSansBold18pt7b)

// ── Arc geometry macros ───────────────────────────────────────────────────────
#define ARC_START      (g_active_theme->arc_start)
#define ARC_END_FULL   (g_active_theme->arc_end_full)
#define ARC_SWEEP      (g_active_theme->arc_sweep)
#define ARC_OUTER      (g_active_theme->arc_outer)
#define ARC_INNER      (g_active_theme->arc_inner)
#define ARC_VOL_OUTER  (g_active_theme->arc_vol_outer)
#define ARC_VOL_INNER  (g_active_theme->arc_vol_inner)
#define ARC_DECO_OUTER (g_active_theme->arc_deco_outer)
#define ARC_DECO_INNER (g_active_theme->arc_deco_inner)
#define ARC_CAP_DIST   (g_active_theme->arc_cap_dist)
#define ARC_CAP_HALO   (g_active_theme->arc_cap_halo)
#define ARC_CAP_DOT    (g_active_theme->arc_cap_dot)

// ── Display geometry (never changes — not part of ThemeDef) ──────────────────
static constexpr int CENTER_X = 120;
static constexpr int CENTER_Y = 120;
