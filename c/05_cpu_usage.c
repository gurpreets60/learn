/*
 * 05 — CPU usage (live)    (same goal as sh/05_cpu_usage.sh)
 *
 * NEW IN C struct            group related values into one thing you can copy
 *          unsigned long long counters that only grow → %llu
 *          sleep / nanosleep  wait without burning CPU
 *          fflush(stdout)     why isn't my output showing up yet?
 *
 * CHECK    top ; your sh version side by side
 *
 * HINTS
 *   H1  A format of "cpu %llu %llu %llu ..." with 8 conversions reads the
 *       first line. sscanf returns how many it matched: expect 8.
 *   H2  Structs can be assigned: prev = cur; copies every field.
 *   H3  To sample faster than 1 s, look at nanosleep (man 2 nanosleep) and
 *       struct timespec { .tv_sec = 0, .tv_nsec = 500000000 }.
 *   H4  Pipe it:  ./bin/05_cpu_usage | cat   — does output lag? Why?
 *       (stdout is line-buffered on a terminal and block-buffered on a pipe.)
 *
 * BONUS    per-core: keep reading lines while they start with "cpu" + digit.
 *          An array of structs, one per core.
 */
#include <stdio.h>
#include <unistd.h>

struct cpu_times {
    unsigned long long total;
    unsigned long long idle;
};

/* Fill *t from the first line of /proc/stat. 0 on success, -1 on failure. */
static int read_times(struct cpu_times *t)
{
    FILE *f = fopen("/proc/stat", "r");
    if (!f) {
        perror("/proc/stat");
        return -1;
    }
    /* TODO: read 8 counters; total = their sum; idle = idle + iowait */
    t->total = 0;
    t->idle = 0;
    fclose(f);
    return 0;
}

int main(void)
{
    struct cpu_times prev, cur;
    if (read_times(&prev) != 0)
        return 1;

    for (;;) {
        sleep(1);
        if (read_times(&cur) != 0)
            return 1;

        /* TODO: Δtotal, Δidle → busy % (guard Δtotal == 0) */
        printf("cpu: TODO%%\n");

        prev = cur;
    }
}
