#!/bin/sh
# 01 — CPU info
#
# GOAL     Print the CPU model name, the number of logical CPUs, and the
#          current clock (MHz) of each one:
#              Model : AMD Ryzen ...
#              CPUs  : 16
#              cpu 0 : 1400.000 MHz
#              ...
#
# WHERE    /proc/cpuinfo — not a real file. The kernel writes the text
#          fresh every time you read it (run `ls -l` on it: size 0!).
#
# EXPLORE  less /proc/cpuinfo
#          grep -c . /proc/cpuinfo      # what does this count? is it what you want?
#
# CHECK    lscpu ; nproc
#
# HINTS    Read one at a time, only when stuck.
#   H1  The file is blocks of "key<TAB>: value" lines, one block per CPU.
#   H2  Exactly one line per block starts with "processor".
#   H3  grep -m1 stops at the first match. cut -d: -f2 or sed 's/.*: //'
#       drops the key.
#   H4  For TODO 3: grep gives you all the "cpu MHz" lines in order. Something
#       has to number them. `nl`? A while-read loop with a counter? awk's NR?

set -eu   # -e: stop on error, -u: error on unset variables (try misspelling one)

CPUINFO=/proc/cpuinfo

# TODO 1: model name, just the value, without "model name : " in front.
#         Careful: two different keys start with "model".
model="TODO"

# TODO 2: how many logical CPUs? Count something that appears once per CPU.
count="TODO"

echo "Model : $model"
echo "CPUs  : $count"

# TODO 3: one line per CPU:  "cpu N : XXXX MHz"
