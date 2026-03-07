# Waveshare LCD Knob — ESPHome Home Assistant Controller

An [ESPHome](https://esphome.io) firmware for the **Waveshare ESP32-S3 LCD Knob** that turns the device into a modular Home Assistant controller.  Out of the box it works as a Sonos media player, with additional screens (Meater+ probe thermometer, and more) that can be enabled with a single `used: true` flag.

> **ESPHome ≥ 2024.2 required**

---

## Hardware

**Waveshare ESP32-S3-LCD-Knob**

- ESP32-S3, 8 MB flash
- 240×240 round display (GC9A01A, SPI)
- EC11 rotary encoder with push button
- CST816S capacitive touch panel
- Passive buzzer

> **Note:** the current firmware still uses the M5Unified / M5Dial Arduino libraries for hardware abstraction while the native Waveshare display and touch bring-up is completed.  A full migration to direct LovyanGFX + GPIO drivers is in progress on the `claude/esp32-s3-migration-plan` branch.

---

## Navigation

```
Double-tap screen  →  open / close MENU

In MENU
  Encoder          →  highlight a group (Sonos / Meater / …)
  Short press      →  enter highlighted group
  Long press       →  cancel, return to current screen

In a group
  Long press       →  cycle pages within group
                       Sonos: Playlist → Now Playing → Volume → (wrap)
  Encoder          →  page-specific (scroll playlist, skip track, change volume)
  Short press      →  page-specific (play playlist, play/pause)
  Double-tap       →  open MENU
```

---

## Screens

### Sonos (3 pages)

| Page | Display | Encoder | Short press |
|------|---------|---------|-------------|
| **Playlist** | Favourite name carousel | Browse favourites | Play selected + shuffle |
| **Now Playing** | Track title + artist, play/pause icon | Skip ▶▶ / ◀◀ | Play/pause |
| **Volume** | Arc + percentage | ±2 % per click | Play/pause |

### Meater+ probe

Displays the internal probe temperature, a progress arc toward the target temperature, and the ambient temperature.  Requires a Meater+ integrated in Home Assistant.

### Adding your own screen

1. Create `components/lcd_knob/screen_foo.h` and `screen_foo.cpp` implementing the `Screen` base class.
2. Add `ScreenKind::FOO` and `configure_foo(…)` to `lcd_knob.h/.cpp`.
3. Add the type to `__init__.py`'s `SCREEN_TYPE_SCHEMAS`.
4. In `lcd-knob.yaml` add a `- type: foo` entry under `screens:`.

---

## Getting started

### 1. Prerequisites

- Home Assistant with the [ESPHome add-on](https://esphome.io/guides/getting_started_hassio.html), or the [ESPHome CLI](https://esphome.io/guides/getting_started_command_line.html).
- Sonos integrated in Home Assistant (Settings → Devices & Services → Sonos).
- USB-C cable for the first flash.

### 2. Clone and configure

```bash
git clone https://github.com/maar0005/lcd-knob-ha
cd lcd-knob-ha
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml`:

```yaml
wifi_ssid:          "MyNetwork"
wifi_password:      "s3cr3t"
ota_password:       "choose_a_password"
api_encryption_key: "base64_32_byte_key"   # esphome config generate-key
```

Edit the **CONFIGURATION** block at the very top of `lcd-knob.yaml` — that is the only section you need to touch:

```yaml
substitutions:
  device_name:   "lcd-knob"
  friendly_name: "LCD Knob"
  timezone:      "Europe/Copenhagen"   # ← your timezone
  sonos_entity:  "media_player.living_room"  # ← your entity ID
  volume_step:   "2"
  screen_off_time:     "30000"
  long_press_duration: "800ms"
```

To enable the Meater screen, also set:

```yaml
  meater_entity_temperature: "sensor.meater_probe_1_internal_temperature"
  meater_entity_target:      "sensor.meater_probe_1_target_temperature"
  meater_entity_ambient:     "sensor.meater_probe_1_ambient_temperature"
```

Then under `screens:` set `used: true` for Meater, and uncomment the matching `sensor:` subscription block.

### 3. Flash

```bash
# First flash over USB
esphome run lcd-knob.yaml

# Subsequent OTA updates
esphome run lcd-knob.yaml --device <ip-address>
```

Or copy the YAML + secrets into your ESPHome Dashboard and flash from there.

---

## File overview

| Path | Purpose |
|------|---------|
| `lcd-knob.yaml` | Main ESPHome config — user settings at the top |
| `secrets.yaml.example` | Credentials template — copy to `secrets.yaml` |
| `components/lcd_knob/` | Custom ESPHome component |
| `components/lcd_knob/__init__.py` | ESPHome schema + code generation |
| `components/lcd_knob/lcd_knob.h/.cpp` | Orchestrator: screen list, input routing, touch detection |
| `components/lcd_knob/screen.h/.cpp` | Abstract `Screen` base + shared colours + draw helper |
| `components/lcd_knob/screen_menu.h/.cpp` | MENU carousel screen |
| `components/lcd_knob/screen_sonos.h/.cpp` | Playlist, Now Playing, Volume screens (share `SonosState`) |
| `components/lcd_knob/screen_meater.h/.cpp` | Meater+ probe temperature screen |
| `ha_automation_example.yaml` | Optional HA automations that react to knob activity |

---

## Troubleshooting

**"No favourites" on the Playlist screen**
1. Confirm you have favourites saved in the Sonos app.
2. Check that `sonos_entity` matches exactly the HA entity ID (Settings → Entities).
3. Run `esphome logs lcd-knob.yaml` and look for `[lcd_knob]` lines.
4. Verify `homeassistant_states: true` is in the `api:` block.

**Button timing feels off**
Adjust `long_press_duration` in the substitutions block (default `800ms`).

**Backlight never dims**
Set `screen_off_time` to a positive number of milliseconds (e.g. `30000` = 30 s).

**OTA fails**
Verify `ota_password` in `secrets.yaml` matches the value used on first flash.  Re-flash over USB if OTA is completely broken.

---

## Contributing

Issues and pull requests welcome.  When reporting a bug please include:
- ESPHome version (`esphome version`)
- Relevant lines from `esphome logs lcd-knob.yaml`
- Expected vs actual behaviour
