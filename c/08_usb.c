/*
 * 08 — USB devices         (same goal as sh/08_usb.sh)
 *
 * NEW IN C glob as a FILTER   match only what you want, skip the rest
 *          default values     a missing file is normal, not an error
 *
 * CHECK    lsusb ; your sh version
 *
 * HINTS
 *   H1  Only real devices have idVendor. So glob FOR THAT FILE:
 *       "/sys/bus/usb/devices/ * /idVendor" (without the spaces). Every match
 *       is one device, and the path's directory is the device dir.
 *   H2  Path surgery again (lesson 04): strrchr for the last '/'.
 *   H3  Make read_str fill in "?" on failure, so callers can ignore errors.
 *       Is that a good API? When would it bite you?
 *   H4  Device name ("3-1") = the text between the last two slashes.
 */
#include <glob.h>
#include <stdio.h>
#include <string.h>

/* TODO: read_str(dir, file, buf, n) that falls back to "?" */

int main(void)
{
    glob_t g;
    /* TODO: glob pattern for real devices only (see H1) */
    int rc = glob("/sys/bus/usb/devices/*", 0, NULL, &g);
    if (rc != 0) {
        fprintf(stderr, "no USB devices?\n");
        return 1;
    }

    for (size_t i = 0; i < g.gl_pathc; i++) {
        /* TODO: dir → name, idVendor:idProduct, speed, manufacturer, product */
        printf("%s  TODO\n", g.gl_pathv[i]);
    }
    globfree(&g);
    return 0;
}
