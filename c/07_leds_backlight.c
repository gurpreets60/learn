/*
 * 07 — LEDs & backlight: WRITING    (same goal as sh/07_leds_backlight.sh)
 *
 *   ./bin/07_leds_backlight caps          (needs: sudo)
 *   ./bin/07_leds_backlight light
 *   ./bin/07_leds_backlight light 40      (needs: sudo)
 *
 * NEW IN C fopen(path, "w") + fprintf   writing a value
 *          errno / EACCES                "why did it fail?", as a number
 *          fclose's return value         sysfs writes can fail AT CLOSE
 *          strtol + endptr               parse a number, and REJECT "4x0"
 *
 * CHECK    Run it WITHOUT sudo first and read the error. Then with sudo.
 *
 * HINTS
 *   H1  perror(path) after a failed fopen prints "…: Permission denied".
 *       errno == EACCES (from <errno.h>) lets you print a friendlier hint.
 *   H2  stdio buffers your fprintf. The real write(2) happens at fflush or
 *       fclose. So if the kernel rejects the value, which call reports it?
 *       Try writing "banana" and check both return values.
 *   H3  strtol(s, &end, 10): after the call, *end must be '\0' and end != s.
 *       Otherwise the input wasn't a clean number.
 *   H4  Clamp: if (pct < 5) pct = 5; ... A screen at 0 is black, and you'd
 *       have to fix it blind.
 *   H5  glob() from lesson 04 finds "input*::capslock" and backlight "*".
 */
#include <errno.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Find the first path matching pattern → out. 0 on success. */
static int find_one(const char *pattern, char *out, size_t n)
{
    /* TODO: glob, copy gl_pathv[0], globfree */
    (void)pattern;
    (void)out;
    (void)n;
    return -1;
}

static int read_long(const char *path, long *out)
{
    /* TODO */
    (void)path;
    *out = 0;
    return -1;
}

/* The core of the lesson. Return 0 only if the value REALLY got written. */
static int write_long(const char *path, long value)
{
    /* TODO: fopen "w" (explain EACCES nicely), fprintf, check fclose */
    (void)path;
    (void)value;
    return -1;
}

static int caps_toggle(void)
{
    /* TODO: find the LED, read it, write !value */
    return 1;
}

static int light(const char *arg)   /* arg == NULL → just print */
{
    /* TODO: find dir, read brightness + max_brightness
     *       print %, or parse arg → clamp 5..100 → write raw */
    (void)arg;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1], "caps") == 0)
        return caps_toggle();
    if (argc >= 2 && strcmp(argv[1], "light") == 0)
        return light(argc >= 3 ? argv[2] : NULL);

    fprintf(stderr, "usage: %s caps | light [PERCENT]\n", argv[0]);
    (void)find_one;
    (void)read_long;
    (void)write_long;
    return 2;
}
