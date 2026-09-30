#!/bin/sh
# 07 — LEDs & backlight: your first WRITES to hardware
#
# GOAL     sh 07_leds_backlight.sh caps        toggle the Caps Lock LED
#          sh 07_leds_backlight.sh light       print screen brightness in %
#          sh 07_leds_backlight.sh light 40    set it to 40%  (never below 5)
#
# WHERE    /sys/class/leds/input*::capslock/brightness     0 or 1
#          /sys/class/backlight/*/brightness               0 .. max_brightness
#          /sys/class/backlight/*/max_brightness
#
# EXPLORE  ls /sys/class/leds/ /sys/class/backlight/
#          ls -l /sys/class/backlight/*/brightness     # who may write it?
#          echo 1 > /sys/class/leds/input2::capslock/brightness   # what error?
#
# CHECK    Look at the Caps Lock key's light, and at the screen. :)
#          brightnessctl   (prints the same number you compute)
#
# HINTS
#   H1  `sudo echo 1 > file` STILL fails. Who opens `file` for writing: your
#       shell or sudo? Work out which process does the redirection.
#   H2  Fix: let a root process do the writing.  echo 1 | sudo tee FILE
#       tee also copies to stdout. Send that to >/dev/null.
#   H3  Only the write needs root. Reading works as you. Least privilege:
#       don't run the whole script under sudo.
#   H4  percent → raw: raw = pct * max / 100. raw → percent: the reverse.
#   H5  The LED may flip back when you press a key. The keyboard driver
#       owns it. Which file in the LED's directory decides what drives it?
#       (cat .../trigger)

set -eu

caps_toggle() {
    # TODO: find the capslock LED file (glob), read it, write the opposite
    :
}

light() {
    # TODO: find the backlight dir (glob — don't hardcode amdgpu_bl1)
    # TODO: no argument → print current %
    # TODO: argument → clamp to 5..100, convert to raw, write it with sudo
    :
}

case "${1:-}" in
    caps)  caps_toggle ;;
    light) shift; light "$@" ;;
    *)     echo "usage: $0 caps | light [PERCENT]" >&2; exit 2 ;;
esac
