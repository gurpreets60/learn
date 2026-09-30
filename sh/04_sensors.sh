#!/bin/sh
# 04 — Temperature sensors & fans
#
# GOAL     One line per temperature sensor and per fan:
#              k10temp    temp1  Tctl        54.2 °C
#              nvme       temp1  Composite   38.8 °C
#              hp         fan1   -           2300 RPM
#
# WHERE    /sys/class/hwmon/hwmon*/
#              name          which driver (k10temp = CPU, amdgpu = iGPU, ...)
#              tempN_input   temperature in MILLIdegrees C
#              tempN_label   optional human name
#              fanN_input    RPM
#
# EXPLORE  for h in /sys/class/hwmon/hwmon*; do echo "$h: $(cat "$h/name")"; done
#          ls /sys/class/hwmon/hwmon5/
#
# CHECK    sensors
#
# HINTS
#   H1  54250 millidegrees = 54.2 °C. Whole part: / 1000. Tenth: think %.
#   H2  A glob that matches nothing stays as the literal text
#       ".../temp*_input". Test with [ -e "$t" ] || continue.
#   H3  ${t##*/} strips everything up to the last '/' (like basename).
#       ${t%_input} strips a suffix. Put them together and you get "temp1".
#   H4  The label is optional:  cat "$x" 2>/dev/null || echo -
#   H5  printf '%-10s %-6s %-10s' lines up columns. echo can't do that.
#
# BONUS    hwmonN numbers can change between boots. What stays the same?
#          (ls -l /sys/class/hwmon/ — where do the links point?)

set -eu

for h in /sys/class/hwmon/hwmon*; do
    name="TODO"

    for t in "$h"/temp*_input; do
        # TODO: skip the no-match case
        # TODO: id (temp1), label, value → "54.2"
        :
    done

    # TODO: same idea for fan*_input (RPM, no conversion)
done
