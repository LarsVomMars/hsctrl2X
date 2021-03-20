#!/bin/env python
from gi import require_version

require_version('Gtk', '3.0')
require_version('AppIndicator3', '0.1')
require_version('Notify', '0.7')

from subprocess import check_output, CalledProcessError
from gi.repository import Gtk, GLib, AppIndicator3, Notify


Notify.init("headset-charge-notify")

MAX_BATTERY_LIFE = 16

class Handler:
    notified = False
    charging = False
    charge_notify = Notify.Notification.new(
        "hsctrl2gnome", "Battery low", "dialog-warning"
    )
    panel = None

    @staticmethod
    def get_battery():
        try:
            return int(check_output(["headsetcontrol", "-b", "-c"]))
        except CalledProcessError:
            return -2

    @staticmethod
    def update(_=None):
        battery = Handler.get_battery()
        battery_state = None
        if battery == -2:
            battery_state = "Off"
        elif battery == -1:
            battery_state = "Charging"
            Handler.notified = True
            Handler.charging = True
        elif 0 <= battery <= 100:
            Handler.charging = False
            battery_state = f"{battery}% (~{'{:.2f}'.format(round(battery * (MAX_BATTERY_LIFE / 100), 2))}h)"
        else:
            battery_state = "W8, what?"

        Handler.panel.set_label(battery_state, "100%")

        if 0 <= battery < 10 and not Handler.notified and not Handler.charging:
            Handler.charge_notify.set_timeout(0)
            Handler.charge_notify.show()
            Handler.notified = True

        return True


Handler.panel = AppIndicator3.Indicator.new(
    "headset-charge",
    "audio-headset",
    AppIndicator3.IndicatorCategory.HARDWARE
)

Handler.panel.set_status(AppIndicator3.IndicatorStatus.ACTIVE)
menu = Gtk.Menu()
Handler.panel.set_menu(menu)

GLib.timeout_add(60000, Handler.update, None)
Handler.update()
Gtk.main()
