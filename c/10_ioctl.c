/*
 * 10 — ioctl: asking the driver directly   (see sh/10_ioctl.sh first)
 *
 * ioctl(fd, REQUEST, &something) is the "everything else" syscall. When a
 * device needs more than read/write, the driver defines requests, and
 * each request says what struct it fills in or reads from.
 *
 *   ./bin/10_ioctl          list input devices + terminal size
 *   ./bin/10_ioctl beep     BONUS: write a tone to the PC speaker device
 *
 * NEW IN C ioctl(2)                            <sys/ioctl.h>
 *          EVIOCGNAME(len), EVIOCGID           <linux/input.h>
 *          TIOCGWINSZ + struct winsize         your TERMINAL is a device too
 *          write(2) of a struct                sending an event TO a driver
 *
 * CHECK    your sh version: same names, same IDs, same size?
 *          strace -e trace=ioctl ./bin/10_ioctl
 *
 * HINTS
 *   H1  EVIOCGNAME(sizeof name) is a MACRO that builds the request number,
 *       including the buffer length. The call looks like:
 *           ioctl(fd, EVIOCGNAME(sizeof name), name)
 *       It returns < 0 on error.
 *   H2  EVIOCGID fills a struct input_id. Find its fields with
 *       grep -n 'struct input_id' -A6 /usr/include/linux/input.h
 *   H3  Terminal size: the fd is STDIN_FILENO (or STDOUT). Try both with
 *       output piped to cat. Which one still works, and why?
 *   H4  beep: the PC speaker is "*-event-spkr" in /dev/input/by-path.
 *       Send { .type = EV_SND, .code = SND_TONE, .value = 880 } (Hz), sleep,
 *       then value 0 to stop. Laptops often have no real speaker hooked up.
 *       If write() succeeds, the lesson worked even if you hear nothing.
 */
#include <fcntl.h>
#include <glob.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static void list_input(void)
{
    glob_t g;
    if (glob("/dev/input/event*", 0, NULL, &g) != 0)
        return;

    for (size_t i = 0; i < g.gl_pathc; i++) {
        char name[256] = "?";
        struct input_id id = {0};
        /* TODO: open read-only, ioctl EVIOCGNAME + EVIOCGID, close
         *       print  eventN  bus:vendor:product (%04x)  name */
        printf("%s  %04x:%04x:%04x  %s\n", g.gl_pathv[i],
               id.bustype, id.vendor, id.product, name);
    }
    globfree(&g);
}

static void term_size(void)
{
    struct winsize ws = {0};
    /* TODO: ioctl TIOCGWINSZ; on failure perror and return */
    printf("terminal: %u rows x %u cols\n", ws.ws_row, ws.ws_col);
}

static int beep(void)
{
    /* TODO (bonus): find the speaker, open WRITE-only, write tone, usleep,
     *               write tone 0 */
    return 1;
}

int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1], "beep") == 0)
        return beep();
    list_input();
    term_size();
    return 0;
}
