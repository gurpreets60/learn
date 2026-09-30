/*
 * 09 — Raw keyboard events (same goal as sh/09_input_events.sh)
 *
 *   ./bin/09_input_events                    (auto-find keyboard)
 *   ./bin/09_input_events /dev/input/event1  (lid switch? power button?)
 *
 * NEW IN C open / read / close  the raw syscalls under fopen/fread
 *          struct input_event   the kernel hands you C structs directly!
 *          ssize_t              read can return: bytes, 0 (EOF), or -1
 *
 * CHECK    libinput debug-events ; your sh version
 *
 * HINTS
 *   H1  <linux/input.h> already defines struct input_event, EV_KEY, KEY_A ...
 *       You never parse the bytes. You read(fd, &ev, sizeof ev).
 *   H2  printf("%zu\n", sizeof(struct input_event)). Does it match the
 *       24 you used in sh?
 *   H3  read() returning less than sizeof ev means something is wrong.
 *       Treat it as an error.
 *   H4  Key names: a static array with designated initializers:
 *           static const char *names[KEY_MAX + 1] = { [KEY_A] = "A", ... };
 *       Add a dozen. Print the number when a name is NULL.
 *   H5  O_RDONLY is enough. Why not fopen here? (It would work, but where
 *       would the buffering sit, and what would that do to one keypress?)
 */
#include <fcntl.h>
#include <glob.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* TODO: a key-name table (see H4) */

static int find_keyboard(char *out, size_t n)
{
    /* TODO: glob "/dev/input/by-path/ *-event-kbd" (no spaces), take the first */
    (void)out;
    (void)n;
    return -1;
}

int main(int argc, char **argv)
{
    char path[256];
    if (argc >= 2)
        snprintf(path, sizeof path, "%s", argv[1]);
    else if (find_keyboard(path, sizeof path) != 0) {
        fprintf(stderr, "keyboard device not found\n");
        return 1;
    }

    int fd = -1;
    /* TODO: open path read-only; perror + return 1 on failure */
    if (fd < 0) {
        fprintf(stderr, "TODO: open %s\n", path);
        return 1;
    }
    printf("reading %s — type something, Ctrl-C to stop\n", path);

    struct input_event ev;
    for (;;) {
        /* TODO: read one event (check the size!)
         *       EV_KEY only → "key %u  down/up/repeat" (+ name if known) */
        (void)ev;
        break;
    }
    close(fd);
    return 0;
}
