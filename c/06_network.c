/*
 * 06 — Network interfaces  (same goal as sh/06_network.sh)
 *
 * NEW IN C argc / argv       command-line arguments
 *          d_type + stat     what IS this directory entry?
 *          access(2)         does a path exist?  access(p, F_OK) == 0
 *
 * CHECK    ip -s link ; your sh version
 *
 * HINTS
 *   H1  argc counts the program name too. "./06_network wlo1" has argc == 2.
 *   H2  The trap: everything in /sys/class/net is a SYMLINK. If you filter
 *       with d_type == DT_DIR, you'll print nothing. Print e->d_type for
 *       each entry, then look up DT_LNK in <dirent.h>.
 *   H3  Wi-Fi check: access("<dir>/wireless", F_OK) == 0
 *   H4  bytes / (1024.0 * 1024.0) → MiB as a double.
 */
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NET_DIR "/sys/class/net"

/* TODO: read_str / read_ull helpers (third time: getting faster?) */

static void list_all(void)
{
    DIR *d = opendir(NET_DIR);
    if (!d) {
        perror(NET_DIR);
        return;
    }
    struct dirent *e;
    while ((e = readdir(d))) {
        /* TODO: skip ".", "..", "lo"
         *       state, wifi/wired, mac, rx/tx MiB → one row */
        printf("%s (type %d)  TODO\n", e->d_name, e->d_type);
    }
    closedir(d);
}

static int watch_one(const char *iface)
{
    /* TODO: check NET_DIR/iface exists, then loop:
     *       read rx/tx, sleep(1), read again, print KiB/s */
    (void)iface;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        list_all();
        return 0;
    }
    return watch_one(argv[1]);
}
