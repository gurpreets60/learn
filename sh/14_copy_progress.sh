#!/bin/sh
# 14 — Copy a file with a progress bar
#
# GOAL     sh 14_copy_progress.sh SRC DST
#              [##########..........]  50%  512/1024 MiB
#          Refuse if DST exists. At the end, check the copy matches.
#
# MAKE A TEST FILE (1 GiB of zeros, instant because it's sparse... is it?):
#          truncate -s 1G ~/learn/sandbox/big.bin
#          head -c 300M /dev/urandom > ~/learn/sandbox/rand.bin   # real data
#
# WHERE    dd copies in fixed-size blocks, and you control where each block
#          comes from and goes to:
#              bs=1M        block size
#              count=K      only K blocks
#              skip=I       start I blocks into the INPUT
#              seek=I       start I blocks into the OUTPUT
#              conv=notrunc don't wipe the output on each call
#
# CHECK    cmp SRC DST && echo same    ;    sha256sum SRC DST
#          (dd status=progress is the built-in cheat. Compare your bar to it.)
#
# HINTS
#   H1  Size in bytes: stat -c %s. Number of 1 MiB blocks: round UP.
#       How do you round up with integer division?
#   H2  One dd per block: dd if=SRC of=DST bs=1M count=1 skip=$i seek=$i
#       conv=notrunc status=none. (Slow-ish. Why? Count the processes.)
#   H3  printf '\r...' goes back to the start of the line without a
#       newline, so the next print draws over the bar. One final echo at
#       the end.
#   H4  The bar: filled = pct * 20 / 100. Build it with a small while loop,
#       or printf '%*s' plus tr ' ' '#'.
#   H5  After copying rand.bin, run ls -ls on SRC and DST (first column =
#       blocks on disk). Then do big.bin. Do the sparse file's holes
#       survive your copy?

set -eu

src="${1:-}"
dst="${2:-}"
[ -f "$src" ] && [ -n "$dst" ] || { echo "usage: $0 SRC DST" >&2; exit 2; }
# TODO: refuse if dst exists

# TODO: size, number of blocks

i=0
# TODO: while i < blocks: dd one block, draw the bar, i=$((i+1))

echo
# TODO: verify with cmp
