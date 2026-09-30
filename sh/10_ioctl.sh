#!/bin/sh
# 10 — ioctl, seen from the shell
#
# The shell CAN'T call ioctl(2), the "special request to a driver" syscall.
# But the kernel mirrors much of that info into sysfs, and some tools make
# the call for you. This lesson finds both. The C side (c/10_ioctl.c) makes
# the calls directly.
#
# GOAL     1. Every input device: node, bus/vendor/product IDs, name
#                event2  0011:0001:0001  AT Translated Set 2 keyboard
#          2. Your terminal's size:   rows x cols
#
# WHERE    /sys/class/input/eventN/device/name
#          /sys/class/input/eventN/device/id/{bustype,vendor,product}
#          stty size        ← this tool calls ioctl for you
#
# EXPLORE  ls /sys/class/input/event2/device/ /sys/class/input/event2/device/id/
#          stty size
#          strace -e trace=ioctl stty size      ← find the request name!
#
# CHECK    cat /proc/bus/input/devices  ;  resize the terminal, run again
#
# HINTS
#   H1  Same loop shape as lessons 04 and 08: glob, read a few files, print.
#   H2  set -- $(stty size) puts rows in $1 and cols in $2. (What's the
#       catch? Your script's own arguments are gone now.)
#   H3  stty size run in a pipe or under `a` might fail. Its stdin must be
#       a terminal. Why stdin and not stdout? (strace shows the fd number.)
#
# THINK    printf '\a' rings the terminal "bell". Does that go to the PC
#          speaker device at all? Who decides what a bell does?

set -eu

echo "== input devices"
for e in /sys/class/input/event*; do
    # TODO: short name (event2), ids as bus:vendor:product, device name
    :
done

echo "== terminal"
# TODO: rows x cols
