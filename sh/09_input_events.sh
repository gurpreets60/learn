#!/bin/sh
# 09 — Raw keyboard events from /dev/input
#
# GOAL     Print every key press / release straight from the keyboard
#          driver, until Ctrl-C:
#              key 30  down
#              key 30  up
#              key 42  down  (repeat)
#          Then look up the numbers: 30 = KEY_A.
#
# WHERE    /dev/input/eventN   a DEVICE NODE. Reading it hands you a stream
#                              of BINARY records, one per event:
#
#          struct input_event {         (x86_64: 24 bytes)
#              struct timeval time;     16 bytes: seconds + microseconds
#              __u16 type;              2   (1 = EV_KEY)
#              __u16 code;              2   (which key)
#              __s32 value;             4   (0 up, 1 down, 2 repeat)
#          };
#
# EXPLORE  ls -l /dev/input/by-path/          which eventN is the keyboard?
#          cat /proc/bus/input/devices         names ↔ eventN
#          od -An -tx1 -w24 /dev/input/event2  press keys, look at the hex, Ctrl-C
#          grep 'KEY_A\b' /usr/include/linux/input-event-codes.h
#
# CHECK    libinput debug-events
#
# NOTE     This works without sudo because you're in the `input` group.
#          That also means ANY program you run can read your keystrokes.
#          Worth knowing.
#
# HINTS
#   H1  od -t u2 prints each 2 bytes as an unsigned number. That makes 12
#       numbers per 24-byte record. Which positions are type, code, value?
#   H2  -v stops od from collapsing repeated lines into "*".
#       -An drops the offset column.
#   H3  Nothing prints until you've typed a LOT? od's output is going into a
#       pipe, and stdio buffers pipes in 4 KiB blocks. Look at `man stdbuf`.
#   H4  `read -r a b c d e f g h type code val rest` splits one od line.
#   H5  Each keypress also sends type-0 records (EV_SYN, "end of packet")
#       and type-4 (EV_MSC scancodes). Filter for type 1.
#   H6  The first event you see is releasing Enter from starting the
#       script. :)
#
# BONUS    The lid switch: find the "Lid Switch" eventN, watch for type 5
#          (EV_SW), and gently tilt the lid shut.

set -eu

# TODO 1: find the keyboard's event device (by-path, "*-event-kbd")
dev=""
[ -e "$dev" ] || { echo "keyboard device not found" >&2; exit 1; }

echo "reading $dev — type something, Ctrl-C to stop"

# TODO 2: od (unbuffered) | while read ... ; do filter + print ; done
