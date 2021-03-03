# hsctrl2X

Based on [headsetcontrol](https://github.com/Sapd/HeadsetControl) **hsctrl2X** creates a battery percentage panel for gnome via [KStatusNotifierItem/AppIndicator](https://extensions.gnome.org/extension/615/appindicator-support/) or for [slstatus](https://tools.suckless.org/slstatus/).

## Requirements
### Gnome

- libappindicator (gtk3)
- libnotify
- python-gobject
- [headsetcontrol](https://github.com/Sapd/HeadsetControl)
- [KStatusNotifierItem/AppIndicator](https://extensions.gnome.org/extension/615/appindicator-support/)

### slstatus
- [headsetcontrol](https://github.com/Sapd/HeadsetControl)

## Setup

### Gnome
- Update `MAX_BATTERY_LIFE` accordingly to your headset
- Install requirements
- Test: `python hsctrl2gnome.py` or `./hsctrl2gnome.py`
- If everything works: Run `./setup` which will add **hsctrl2gnome** to gnome's autostart

### slstatus
- Update `MAX_BATTERY` accordingly to your headset
- Add `headsetcontrol.c` to `slstatus/components/` and add it to `slstatus/Makefile`
- Re`$ make` and re`# make install` slstatus
- Restart slstatus

> Have fun!

### Idea and credits

This is a simplified version of [headset-charge-indicator](https://github.com/centic9/headset-charge-indicator)
