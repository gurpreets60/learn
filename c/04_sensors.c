/*
 * 04 — Temperature sensors & fans   (same goal as sh/04_sensors.sh)
 *
 * NEW IN C glob(3)           the shell's * wildcard, as a library call
 *          path surgery      "dir/temp1_input" → "dir" and "temp1"
 *          "%.*s"            printf only the first N chars of a string
 *
 * CHECK    sensors ; your sh version
 *
 * HINTS
 *   H1  strrchr(path, '/') points at the LAST slash. Subtract the pointers
 *       (slash - path) to get the directory's length.
 *   H2  snprintf(buf, n, "%.*s/name", (int)len, path) prints just the
 *       first len chars of path, then "/name".
 *   H3  Label path: find "_input" with strstr, copy the part before it,
 *       then add "_label".
 *   H4  Degrees: v / 1000.0 (the .0 matters!). Print with "%.1f".
 *   H5  Many reads here look like lesson 03. Copy your read helpers over.
 *       Retyping them is part of the practice.
 */
#include <glob.h>
#include <stdio.h>
#include <string.h>

/* TODO: bring over (or rewrite) small read_str / read_long helpers.
 *       This time they can take a single full path. */

static void list(const char *pattern, int is_temp)
{
    glob_t g;
    int rc = glob(pattern, 0, NULL, &g);
    if (rc == GLOB_NOMATCH)
        return;
    if (rc != 0) {
        fprintf(stderr, "glob(%s) failed: %d\n", pattern, rc);
        return;
    }

    for (size_t i = 0; i < g.gl_pathc; i++) {
        const char *path = g.gl_pathv[i];
        /* TODO 1: read the value
         * TODO 2: dir = path up to the last '/', then read dir/name
         * TODO 3: id  = "temp1" / "fan1" (between the last '/' and "_input")
         * TODO 4: temps only: label (or "-"), and degrees with 1 decimal
         * TODO 5: print one aligned row (%-10s ...) */
        printf("%s  (TODO)\n", path);
    }
    (void)is_temp;
    globfree(&g);
}

int main(void)
{
    list("/sys/class/hwmon/hwmon*/temp*_input", 1);
    list("/sys/class/hwmon/hwmon*/fan*_input", 0);
    return 0;
}
