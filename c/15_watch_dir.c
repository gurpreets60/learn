/*
 * 15 — Watch a directory for changes (KERNEL EVENTS)   (see sh/15_watch_dir.sh)
 *
 *   ./bin/15_watch_dir DIR
 *
 * The sh version polls: it looks every second and compares. Here the
 * kernel TELLS you what happened, right when it happens, using inotify.
 * The program sleeps inside read() until there's news. That's the same
 * "block on read()" model as /dev/input in lesson 09.
 *
 * NEW IN C inotify_init1 / inotify_add_watch   <sys/inotify.h>
 *          variable-length records             one read() can return
 *                                              SEVERAL events of DIFFERENT
 *                                              sizes
 *          bit masks                           ev->mask & IN_CREATE
 *
 * CHECK    same "TRY IT" as the sh version. Delete a file within 1 s of
 *          creating it. Does C catch what sh missed?
 *
 * HINTS
 *   H1  fd = inotify_init1(0);
 *       inotify_add_watch(fd, dir, IN_CREATE | IN_DELETE | IN_MODIFY | ...)
 *       Also look at IN_MOVED_FROM / IN_MOVED_TO and IN_CLOSE_WRITE.
 *   H2  read(fd, buf, sizeof buf) → n bytes holding 1 or more
 *       struct inotify_event, each followed by ev->len bytes of name.
 *   H3  Walk the buffer:
 *           for (char *p = buf; p < buf + n; p += sizeof *ev + ev->len)
 *       with ev = (struct inotify_event *)p at the top of each step.
 *   H4  The buffer must be aligned for the struct. See the EXAMPLES section
 *       of man 7 inotify for the __attribute__((aligned(...))) trick.
 *   H5  `echo hi >> x` gives MODIFY *and* CLOSE_WRITE. Editors often write
 *       a temp file and rename it over the original. Watch what vim does.
 *   H6  inotify is NOT recursive. Subdirectories need their own watches.
 *       How does that change your program?
 */
#include <stdio.h>
#include <sys/inotify.h>
#include <time.h>
#include <unistd.h>

static void print_event(const struct inotify_event *ev)
{
    /* TODO: timestamp (strftime "%T"), a symbol (+ - ~ > <) from ev->mask,
     *       and ev->name (only when ev->len > 0) */
    (void)ev;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s DIR\n", argv[0]);
        return 2;
    }

    int fd = -1;
    /* TODO: inotify_init1 + inotify_add_watch on argv[1] (H1), with perror */
    if (fd < 0) {
        fprintf(stderr, "TODO: set up inotify\n");
        return 1;
    }
    printf("watching %s — Ctrl-C to stop\n", argv[1]);

    char buf[4096];   /* TODO: alignment (H4) */
    for (;;) {
        ssize_t n = read(fd, buf, sizeof buf);
        if (n <= 0) {
            perror("read");
            return 1;
        }
        /* TODO: walk the buffer (H3), print_event each one */
        (void)print_event;
    }
}
