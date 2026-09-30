/*
 * 14 — Copy a file with a progress bar   (same goal as sh/14_copy_progress.sh)
 *
 *   ./bin/14_copy_progress SRC DST [BUFSIZE]
 *
 * NEW IN C read/write loop     the heart of cp, cat, dd, and every other copier
 *          short writes        write() may write LESS than you asked
 *          fstat → st_size     total size, for the percentage
 *          O_CREAT | O_EXCL    "create, but fail if it exists", in ONE step
 *          buffer size         why does it matter? Measure it!
 *
 * CHECK    cmp SRC DST ; time ./bin/14_copy_progress SRC DST 1
 *                        time ./bin/14_copy_progress SRC DST 65536
 *
 * HINTS
 *   H1  Loop: n = read(in, buf, size). n == 0 → done. n < 0 → error.
 *       Otherwise write all n bytes.
 *   H2  "All n bytes" is its own loop: keep calling write() on the part
 *       that isn't written yet, advancing a pointer, until it's all out.
 *   H3  open(dst, O_WRONLY | O_CREAT | O_EXCL, 0644). With EEXIST, refuse.
 *       This beats "check then create" (lesson 13's race). Why?
 *   H4  Redraw the bar only when the percentage CHANGES. Printing on every
 *       4 KiB chunk makes the terminal the bottleneck.
 *   H5  "\r" + fflush(stdout). The bar has no '\n', so without the flush
 *       it sits in stdio's buffer.
 *   H6  BUFSIZE 1 = one syscall per byte. Run it under `strace -c` and
 *       count them.
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/* Write all len bytes, even when write() does it in pieces. 0 ok, -1 error. */
static int write_all(int fd, const char *buf, size_t len)
{
    /* TODO: H2 */
    (void)fd;
    (void)buf;
    (void)len;
    return -1;
}

static void draw_bar(long long done, long long total)
{
    /* TODO: [####......]  NN%  X/Y MiB   with \r and fflush */
    (void)done;
    (void)total;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s SRC DST [BUFSIZE]\n", argv[0]);
        return 2;
    }
    size_t bufsize = argc >= 4 ? (size_t)atol(argv[3]) : 65536;
    if (bufsize == 0)
        bufsize = 65536;

    int in = -1, out = -1;
    /* TODO: open SRC read-only; open DST with H3's flags; fstat(in) for size */

    char *buf = malloc(bufsize);
    if (!buf) {
        perror("malloc");
        return 1;
    }

    long long done = 0, total = 0;
    /* TODO: the copy loop (H1), updating done and calling draw_bar */
    (void)write_all;
    (void)draw_bar;
    (void)done;
    (void)total;

    printf("\n");
    free(buf);
    if (in >= 0)
        close(in);
    /* THINK: close(out) can fail too, e.g. on a full disk. Check it. */
    if (out >= 0)
        close(out);
    return 0;
}
