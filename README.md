# hsctrl2gnome

Based on [headsetcontrol](https://github.com/Sapd/HeadsetControl) **hsctrl2gnome** creates a battery percentage panel for gnome via [KStatusNotifierItem/AppIndicator](https://extensions.gnome.org/extension/615/appindicator-support/)

## Requirements

- libappindicator (gtk3)
- libnotify
- python-gobject
- [headsetcontrol](https://github.com/Sapd/HeadsetControl)
- [KStatusNotifierItem/AppIndicator](https://extensions.gnome.org/extension/615/appindicator-support/)

## Setup

- Add `MAX_BATTERY_LIFE` accordingly to your headset
- Install requirements
- Test: `python hsctrl2gnome.py` or `./hsctrl2gnome.py`
- If everything works: Run `./setup` which will add **hsctrl2gnome** to gnome's autostart

### Idea and credits

This is a simplified version of [headset-charge-indicator](https://github.com/centic9/headset-charge-indicator)
