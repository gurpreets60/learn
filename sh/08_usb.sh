#!/bin/sh
# 08 — USB devices
#
# GOAL     One line per plugged-in USB device:
#              3-1    046d:c52b  12 Mbps   Logitech  USB Receiver
#              1-5    0bda:5634  480 Mbps  ?         HP Wide Vision HD Camera
#          Plug something in or pull it out, run again, and spot the change.
#
# WHERE    /sys/bus/usb/devices/*/
#              idVendor, idProduct   hex IDs (always present on a device)
#              manufacturer, product  strings (OPTIONAL: not every device has them)
#              speed                  Mbps
#
# EXPLORE  ls /sys/bus/usb/devices/
#          Names like "1-5" are devices. "1-5:1.0" are interfaces OF a device,
#          and "usb1" is a root hub. Look inside one of each.
#
# CHECK    lsusb   (pacman -S usbutils, if it's missing)
#
# HINTS
#   H1  Real devices have an idVendor file and interfaces don't.
#       [ -f "$d/idVendor" ] || continue
#   H2  Optional files:  x=$(cat "$d/product" 2>/dev/null) || x="?"
#   H3  Want to skip root hubs (vendor 1d6b = "Linux Foundation")? Look
#       at the names: they start with "usb".
#   H4  Who's who by vendor ID: /usr/share/hwdata/usb.ids, if you have it.
#       grep "^046d" on that file.

set -eu

for d in /sys/bus/usb/devices/*; do
    # TODO: skip non-devices
    # TODO: name, vid:pid, speed, manufacturer, product → one aligned line
    :
done
