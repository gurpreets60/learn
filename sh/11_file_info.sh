#!/bin/sh
# 11 — File info: what IS this path?
#
# GOAL     sh 11_file_info.sh PATH...   → one block per path:
#              /etc/passwd
#                type   : regular file
#                perms  : -rw-r--r--  (644)
#                owner  : root:root
#                size   : 2.9 KiB
#                changed: 2026-09-12 10:31
#              /bin
#                type   : symlink → usr/bin
#
# WHERE    Not /proc or /sys this time. Every file has an INODE: metadata
#          the filesystem keeps apart from the contents. stat(1) and ls -l
#          read it with the stat(2) syscall.
#
# EXPLORE  stat /etc/passwd
#          stat -c '%F|%A|%a|%U|%G|%s|%Y' /etc/passwd /bin /dev/null /tmp
#          man stat    (the FORMAT section lists every %letter)
#
# CHECK    ls -ld PATH ; stat PATH
#
# HINTS
#   H1  One stat -c call can print everything at once, separated by a
#       character that can't appear in the values. Then split it with:
#           IFS='|' read -r type perms ... <<EOF
#           $(stat -c '...' "$p")
#           EOF
#   H2  stat follows symlinks only with -L. Without it you're looking at the
#       link itself. readlink PATH shows where it points.
#   H3  Human size: 1024 steps. B → KiB → MiB → GiB. A loop that divides
#       while size >= 1024, or numfmt --to=iec (cheating, but good to know).
#   H4  date -d @SECONDS '+%F %H:%M' turns an epoch time into a readable one.
#   H5  "$@" (quoted!) is every argument, spaces intact. Try a file named
#       "a b.txt" with and without the quotes.

set -eu

[ $# -gt 0 ] || { echo "usage: $0 PATH..." >&2; exit 2; }

for p in "$@"; do
    echo "$p"
    # TODO: missing path → say so, continue
    # TODO: one stat call → type, perms (both forms), owner:group, size, mtime
    # TODO: symlink → show the target
    # TODO: human-readable size
done
