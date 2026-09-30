/*
 * 03 — Battery             (same goal as sh/03_battery.sh)
 *
 * GOAL     Charge %, status, watts, health %, time left (h:mm).
 *
 * NEW IN C opendir / readdir / closedir   walk a directory
 *          small helpers                  you'll read MANY sysfs files,
 *                                         so write the reader once
 *          long vs int                    how big can a number get?
 *
 * CHECK    upower -i "$(upower -e | grep -i bat)" ; your sh version
 *
 * HINTS
 *   H1  readdir also returns "." and "..". Skip them (strcmp, or d_name[0]).
 *   H2  snprintf(path, sizeof path, "%s/%s", dir, file) builds a path safely.
 *   H3  For read_long: fscanf(f, "%ld", out) == 1 means success.
 *       Or call read_str and then strtol.
 *   H4  energy_full * 100 = 5 300 000 000. The largest 32-bit int is about
 *       2 100 000 000. What type did you use? (long is 64-bit on x86_64.)
 *   H5  Power: printf("%.1f", uw / 1e6). Why 1e6 and not 1000000?
 *       Try both and see.
 */
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define PS_DIR "/sys/class/power_supply"

/* Read dir/file (a one-line sysfs file) into buf, without the '\n'.
 * Returns 0 on success, -1 on failure. */
static int read_str(const char *dir, const char *file, char *buf, size_t n)
{
    char path[512];
    snprintf(path, sizeof path, "%s/%s", dir, file);
    /* TODO: fopen path, fgets into buf, strip '\n', fclose */
    (void)buf;
    (void)n;
    return -1;
}

/* Same, but it's a number. */
static int read_long(const char *dir, const char *file, long *out)
{
    /* TODO */
    (void)dir;
    (void)file;
    *out = 0;
    return -1;
}

/* Write the full path of the first supply whose type is "Battery" into out. */
static int find_battery(char *out, size_t n)
{
    DIR *d = opendir(PS_DIR);
    if (!d) {
        perror(PS_DIR);
        return -1;
    }
    struct dirent *e;
    while ((e = readdir(d))) {
        /* TODO: skip "." and ".."
         *       build PS_DIR/<e->d_name>, read_str its "type",
         *       if it's "Battery" → copy path to out, closedir, return 0 */
    }
    closedir(d);
    (void)out;
    (void)n;
    return -1;
}

int main(void)
{
    char bat[256];
    if (find_battery(bat, sizeof bat) != 0) {
        fprintf(stderr, "no battery found\n");
        return 1;
    }

    char status[32] = "?";
    long capacity = 0, power_uw = 0, e_now = 0, e_full = 0, e_design = 0;
    /* TODO: fill all of these with read_str / read_long */
    (void)read_str;   /* delete these two once you call them */
    (void)read_long;

    printf("Battery : %s\n", bat);
    printf("Charge  : %ld%%  (%s)\n", capacity, status);
    /* TODO: Power (W, 1 decimal), Health (%), and Left (h:mm) when
     *       discharging with power_uw > 0 */
    (void)power_uw;
    (void)e_now;
    (void)e_full;
    (void)e_design;
    return 0;
}
