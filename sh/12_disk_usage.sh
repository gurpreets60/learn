#!/bin/sh
# 12 — Where did my disk space go?
#
# GOAL     sh 12_disk_usage.sh [DIR] [N]     (defaults: $HOME, 10)
#              == biggest files
#              4.2 GiB  /home/you/Downloads/some.iso
#              ...
#              == biggest subdirectories
#              31 GiB   /home/you/.local
#              ...
#              total: 58 GiB in 212345 files
#
# WHERE    The directory TREE itself. find walks it, and du adds up sizes.
#
# EXPLORE  find ~/learn -type f
#          find ~/learn -type f -printf '%s %p\n'     # size + path
#          du -sh ~/*       # vs  du -sh ~/.*   (where do dotfiles hide?)
#          df -h ~          # how big is the whole disk?
#
# CHECK    du -sh DIR  (total) ; ncdu if you have it
#
# HINTS
#   H1  find ... -printf '%s %p\n' | sort -rn | head -n N  gives the biggest
#       files. sort -n is numeric and -r reverses it.
#   H2  Paths with spaces: after the sort, the path is "everything after
#       the first space". read -r size path does exactly that.
#   H3  Subdirectory totals: du -s DIR/*/ DIR/.[!.]*/ ... then sort. Or
#       du -d1 (max depth 1). Compare the outputs.
#   H4  Permission denied spam? 2>/dev/null. But which errors are you
#       hiding along with those?
#   H5  -xdev (find) / -x (du) stay on ONE filesystem. Without it,
#       `sh 12_disk_usage.sh /` would wander into /proc. What size is
#       /proc/kcore? Is it real?
#   H6  File count: find ... | wc -l

set -eu

dir="${1:-$HOME}"
n="${2:-10}"

[ -d "$dir" ] || { echo "not a directory: $dir" >&2; exit 2; }

echo "== biggest files"
# TODO

echo "== biggest subdirectories"
# TODO

# TODO: total size + file count
