#!/bin/sh
# 15 — Watch a directory for changes (POLLING)
#
# GOAL     sh 15_watch_dir.sh DIR    → until Ctrl-C:
#              17:42:01  + new.txt
#              17:42:05  ~ new.txt        (modified)
#              17:42:09  - new.txt        (deleted)
#
# TRY IT   one terminal:  sh 15_watch_dir.sh ~/learn/sandbox
#          another:       cd ~/learn/sandbox; touch x; echo hi >> x; rm x
#
# HOW      Every second: take a SNAPSHOT (name + modification time of every
#          file), compare it with the previous one, and report differences.
#          This is POLLING. The C version asks the kernel to TELL it
#          instead (inotify). After both work, think about which is better.
#
# CHECK    watch -n1 ls -l DIR     (the lazy version of the same idea)
#
# HINTS
#   H1  Snapshot: stat -c '%n|%Y' DIR/* > FILE  (one "name|mtime" per line).
#       An empty dir makes the glob stay literal. What does stat do then?
#   H2  Temp files: snap=$(mktemp). Clean them up on exit with
#       trap 'rm -f "$old" "$new"' EXIT INT
#   H3  New or deleted: compare just the NAMES of the two snapshots.
#       comm -13 = only in new, comm -23 = only in old. comm needs SORTED
#       input.
#   H4  Modified: same name, different mtime. The whole "name|mtime" line
#       differs, but the name is in both. (join -t'|' old new, then compare
#       fields 2 and 3.)
#   H5  %Y has 1-second resolution. Two writes in the same second look
#       like one. Is %.Y better? (man stat)
#   H6  Change something and delete it within 1 s, and polling never sees
#       it. That's a fundamental limit of polling.

set -eu

dir="${1:-}"
[ -d "$dir" ] || { echo "usage: $0 DIR" >&2; exit 2; }

old=$(mktemp)
new=$(mktemp)
# TODO: trap to clean up

snapshot() {
    # TODO: write "name|mtime" lines for everything in $dir, sorted, to "$1"
    : > "$1"
}

snapshot "$old"
echo "watching $dir — Ctrl-C to stop"
while :; do
    sleep 1
    snapshot "$new"
    # TODO: report +, -, ~ with a timestamp (date +%T)
    cp "$new" "$old"
done
