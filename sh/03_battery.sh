#!/bin/sh
# 03 — Battery
#
# GOAL     For the laptop battery, print:
#              Battery : /sys/class/power_supply/BAT1
#              Charge  : 72%  (Discharging)
#              Power   : 7.5 W
#              Health  : 75%        ← capacity left vs. when it was new
#              Left    : 5:01       ← only while discharging (h:mm)
#
# WHERE    /sys/class/power_supply/<name>/
#          The sysfs rule: ONE value per file. Nothing to parse, just read it.
#
# EXPLORE  ls /sys/class/power_supply/
#          cat /sys/class/power_supply/*/type
#          ls /sys/class/power_supply/BAT1/
#          cat /sys/class/power_supply/BAT1/uevent      # all values at once
#
# CHECK    upower -i "$(upower -e | grep -i bat)"
#
# HINTS
#   H1  Don't hardcode BAT1. Another laptop calls it BAT0. Every supply
#       has a `type` file. You want the one whose type is "Battery".
#   H2  Units aren't in the files. They're in the kernel docs:
#       energy_* = µWh, power_now = µW, and 1 W = 1 000 000 µW.
#   H3  On the charger, power_now can be 0. Dividing by it kills the script.
#   H4  hours = energy_now / power_now. Integers only give whole hours.
#       Work in minutes (×60 first), then split with / and %.
#   H5  Leading zero on minutes: printf '%d:%02d\n' "$h" "$m"
#   H6  Some batteries report charge_* (µAh) + current_now (µA) instead.
#       Not this one, but a robust script would check which exists.

set -eu

# TODO 1: find the battery directory. Loop over /sys/class/power_supply/*,
#         read each one's `type`, stop at the first "Battery".
bat=""

if [ -z "$bat" ]; then
    echo "no battery found" >&2
    exit 1
fi

# TODO 2: read the raw values.
#         A helper like  rd() { cat "$bat/$1"; }  keeps this short.
capacity=""
status=""
power_uw=0
energy_now=0
energy_full=0
energy_design=0

echo "Battery : $bat"
echo "Charge  : $capacity%  ($status)"

# TODO 3: watts with one decimal, e.g. 7.5
#         whole = power_uw / 1000000 ... and the tenth?
echo "Power   : TODO W"

# TODO 4: health = energy_full as a % of energy_full_design
echo "Health  : TODO %"

# TODO 5: only when Discharging AND power_uw > 0 → time left as h:mm
