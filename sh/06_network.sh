#!/bin/sh
# 06 — Network interfaces
#
# GOAL     With no argument, list every interface except lo:
#              eno1   down  wired  aa:bb:cc:dd:ee:ff  rx 0 MiB  tx 0 MiB
#              wlo1   up    wifi   11:22:33:44:55:66  rx 82 MiB tx 9 MiB
#          With an argument, watch that one live until Ctrl-C:
#              sh 06_network.sh wlo1
#              wlo1  down  120.3 KiB/s   up  4.1 KiB/s
#
# WHERE    /sys/class/net/<iface>/
#              operstate, address
#              statistics/rx_bytes, statistics/tx_bytes   (bytes since boot)
#              wireless/     ← only exists for Wi-Fi
#
# EXPLORE  ls /sys/class/net/
#          ls /sys/class/net/wlo1/ /sys/class/net/wlo1/statistics/
#
# CHECK    ip -s link
#
# HINTS
#   H1  ${iface##*/} turns /sys/class/net/wlo1 into wlo1.
#   H2  "Does a directory exist?" is [ -d path ]. That tells wifi from wired.
#   H3  Live rate is lesson 05 again: read, sleep 1, read, subtract.
#   H4  One decimal of KiB/s: bytes * 10 / 1024 gives tenths. Then use / 10
#       and % 10.
#   H5  $# is the number of arguments and $1 is the first. With set -u,
#       reading $1 when it's missing is an error. ${1:-} is the safe way.

set -eu

list_all() {
    for dir in /sys/class/net/*; do
        # TODO: name, skip lo, state, wifi/wired, mac, rx/tx in MiB
        :
    done
}

watch_one() {
    dir="/sys/class/net/$1"
    # TODO: fail with a message if $dir doesn't exist
    while :; do
        # TODO: sample rx/tx, sleep 1, sample again, print rates
        sleep 1
    done
}

if [ -z "${1:-}" ]; then
    list_all
else
    watch_one "$1"
fi
