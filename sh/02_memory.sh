#!/bin/sh
# 02 — Memory
#
# GOAL     Print total and available RAM in MiB, and the % in use:
#              Total     : 15623 MiB
#              Available : 9120 MiB
#              Used      : 6503 MiB (41%)
#          Bonus: the same for swap.
#
# WHERE    /proc/meminfo
#
# EXPLORE  head -5 /proc/meminfo
#          What unit are the numbers in? (look at the end of each line)
#
# CHECK    free -m      ("total" and "available" columns)
#
# HINTS
#   H1  Use MemTotal and MemAvailable, not MemFree. Why? Search
#       `man 5 proc` for MemAvailable (/MemAvailable inside man).
#   H2  awk splits each line on whitespace. $1 is the key, $2 the number,
#       and a pattern like /^MemTotal:/ picks the line.
#   H3  $(( )) is integer-only. 37/100 is 0. Multiply BEFORE you divide.
#   H4  kB → MiB is one divide. By what?

set -eu

MEMINFO=/proc/meminfo

# TODO 1: meminfo_kb KEY  → prints that key's number (kB)
#         e.g. meminfo_kb MemTotal  →  15998064
meminfo_kb() {
    echo 0   # TODO: use "$1" and $MEMINFO
}

total_kb=$(meminfo_kb MemTotal)
avail_kb=$(meminfo_kb MemAvailable)

# TODO 2: used = total - available ; pct = used as a % of total
used_kb=0
pct=0

# TODO 3: print in MiB instead of kB
echo "Total     : $total_kb kB"
echo "Available : $avail_kb kB"
echo "Used      : $used_kb kB ($pct%)"
