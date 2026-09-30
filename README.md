# learn — talking to hardware (and files) in sh and C

Fifteen lessons in two tracks: **01–10 hardware**, **11–15 files**. Each one exists twice, with the **same goal**:

    sh/NN_name.sh   ← do this first
    c/NN_name.c     ← then this

## Why this order

Linux exposes almost all hardware as **files**:

| where   | what it is                                  | how you talk to it          |
|---------|---------------------------------------------|-----------------------------|
| `/proc` | kernel + process state, generated on read   | read text, parse it         |
| `/sys`  | the device model — **one value per file**   | read / write a single value |
| `/dev`  | device nodes, a direct line to a driver     | `read` / `write` / `ioctl`  |

In **sh** you get to *explore* the hardware. `cat`, `ls`, and globs let you poke at it
interactively and see what's there.
In **C** you then do by hand what `cat`/`grep`/`awk` were doing for you:
`open`, `read`, parse, and handle every error. By the end you'll know what those tools
actually do.

The lessons move from `/proc` → `/sys` (read) → `/sys` (write) → `/dev` (binary) → `ioctl`.

## How each file works

Every file starts with the same header:

- **GOAL**: what the finished program prints
- **WHERE**: which kernel file(s) hold the answer
- **EXPLORE**: commands to run *by hand* before writing any code
- **CHECK**: a real tool whose output you should match
- **HINTS H1..Hn**: get more specific as they go. Read one, try again, then read the next.

The `TODO`s mark the gaps. Each skeleton already runs or compiles, so you can fill one
TODO at a time and re-run. If you're still stuck after the last hint, ask Claude for
*another hint*, not the answer.

## Running

    sh sh/01_cpu_info.sh
    make -C c                 # build everything into c/bin/
    make -C c run-01_cpu_info # build + run one

Lesson 07 writes to hardware and needs root for that part (the file explains why).

## The bridge: strace

Once a lesson works in both languages, compare what each one actually asks the kernel:

    strace -e trace=openat,read,write,ioctl ./c/bin/03_battery
    strace -f -e trace=openat,read,write,ioctl sh sh/03_battery.sh

The C version makes a handful of syscalls. The sh version forks a `cat` for every
value. Same hardware, same files, very different cost.

## Lessons

| #  | topic          | kernel interface                       | sh idea                    | C idea                               |
|----|----------------|----------------------------------------|----------------------------|--------------------------------------|
| 01 | CPU info       | `/proc/cpuinfo`                        | grep, cut, counting        | fopen / fgets / strncmp              |
| 02 | memory         | `/proc/meminfo`                        | awk fields, `$(( ))`       | sscanf, scansets, integer division   |
| 03 | battery        | `/sys/class/power_supply/*`            | find by `type`, units      | readdir, helpers, 64-bit overflow    |
| 04 | sensors & fans | `/sys/class/hwmon/hwmon*`              | globs, `${var%suffix}`     | glob(3), path surgery                |
| 05 | CPU usage      | `/proc/stat`                           | `read` builtin, deltas     | structs, sleeping, deltas            |
| 06 | network        | `/sys/class/net/*`                     | args, live rates           | readdir + symlinks (DT_LNK)          |
| 07 | LEDs/backlight | `/sys/class/leds`, `/sys/class/backlight` | **writing**, sudo + tee | fopen("w"), errno, fclose errors     |
| 08 | USB devices    | `/sys/bus/usb/devices`                 | missing files, defaults    | glob as a filter                     |
| 09 | keyboard input | `/dev/input/eventN`                    | binary via od, buffering   | open/read, `struct input_event`      |
| 10 | ioctl          | `/dev/input/*`, your terminal          | sysfs mirrors of ioctls    | ioctl: EVIOCGNAME, TIOCGWINSZ, beep  |
|    | **files**      |                                        |                            |                                      |
| 11 | file info      | inodes (`stat`)                        | `stat -c`, IFS splitting   | lstat, mode bits, readlink, strftime |
| 12 | disk usage     | the directory tree                     | find -printf, sort, du     | recursion, top-N list, st_dev        |
| 13 | organize       | mkdir / rename                         | case, `${f##*.}`, dry run  | mkdir EEXIST, rename, lookup table   |
| 14 | copy + progress| read / write                           | dd blocks, `\r` redraws    | read/write loop, short writes, O_EXCL|
| 15 | watch a dir    | polling vs **inotify**                 | snapshots + comm           | inotify, variable-length records     |

## Progress

- [ ] 01 sh  
- [ ] 02 sh
- [ ] 03 sh
- [ ] 04 sh
- [ ] 05 sh
- [ ] 06 sh
- [ ] 07 sh
- [ ] 08 sh
- [ ] 09 sh
- [ ] 10 sh
- [ ] 11 sh
- [ ] 12 sh
- [ ] 13 sh
- [ ] 14 sh
- [ ] 15 sh
- [ ] 01 c
- [ ] 02 c
- [ ] 03 c
- [ ] 04 c
- [ ] 05 c
- [ ] 06 c
- [ ] 07 c
- [ ] 08 c
- [ ] 09 c
- [ ] 10 c
- [ ] 11 c
- [ ] 12 c
- [ ] 13 c
- [ ] 14 c
- [ ] 15 c

## Safety

Lessons 13 and 14 create/move files. Practise on `~/learn/sandbox/`, not your real
folders; 13 is a dry run unless you pass `--doit`.

The hardware lessons only read, except 07. The only thing lesson 07 can do "wrong" is set
the screen to black, so both versions clamp brightness to at least 5%. **Don't** go
writing random `/sys` files as root while exploring. Some of them *do* things.
