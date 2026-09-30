#!/bin/sh
# 05 — CPU usage (live)
#
# GOAL     Every second, print overall CPU usage until Ctrl-C:
#              cpu:  12%
#              cpu:   9%
#          Bonus: per-core usage on one line (cpu0 cpu1 ...).
#
# WHERE    /proc/stat, first line:
#              cpu  user nice system idle iowait irq softirq steal guest guest_nice
#          Each number is TIME spent in that state since boot, in "clock
#          ticks" (usually 100 per second).
#
# EXPLORE  head -1 /proc/stat; sleep 1; head -1 /proc/stat    # what changed?
#          getconf CLK_TCK
#
# CHECK    top   (the %Cpu(s) line: usage = 100 - id)   or htop
#
# HINTS
#   H1  One reading is useless: it's the average since boot. Read twice,
#       a second apart, and use the DIFFERENCE between the readings.
#   H2  `read -r a b c ... < /proc/stat` reads the first line straight into
#       variables, with no cat or awk. Leftover fields pile into the LAST one.
#   H3  idle = idle + iowait.  total = the first 8 numbers added up.
#       (guest time is already counted inside user, so don't add it twice.)
#   H4  busy% = (Δtotal − Δidle) * 100 / Δtotal

set -eu

# Sets TOTAL and IDLE from /proc/stat. (Functions in sh share variables with
# the rest of the script. Handy here, dangerous in big scripts.)
sample() {
    # TODO: read the first line, set TOTAL and IDLE
    TOTAL=0
    IDLE=0
}

sample
prev_total=$TOTAL
prev_idle=$IDLE

while :; do
    sleep 1
    sample
    # TODO: deltas → percentage (what if Δtotal is 0?)
    printf 'cpu: %3s%%\n' "TODO"
    prev_total=$TOTAL
    prev_idle=$IDLE
done
