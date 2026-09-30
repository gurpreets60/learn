/*
 * 12 — Where did my disk space go?   (same goal as sh/12_disk_usage.sh)
 *
 *   ./bin/12_disk_usage [DIR] [N]
 *
 * NEW IN C recursion        a function that calls itself for each subdirectory
 *          lstat + S_ISDIR  decide: descend, count, or skip
 *          a top-N list     keep the N biggest without storing everything
 *          st_blocks        size on disk vs. st_size (sparse files!)
 *
 * CHECK    du -sh DIR ; your sh version
 *
 * HINTS
 *   H1  walk(path): opendir → for each entry (skip "." and "..") → build
 *       child path → lstat → directory? walk(child) : count it.
 *   H2  Use lstat, NOT stat. With stat, a symlink pointing at "." makes
 *       you recurse forever. (Try it on a test dir once you're done.)
 *   H3  Top N: keep an array sorted biggest-first. A new file bigger than
 *       the smallest slot takes that slot, then slides left until the
 *       order is right (one insertion-sort step).
 *   H4  Paths get freed and reused. Store a COPY in the top-N list
 *       (fixed char[PATH_MAX], or strdup + free when it's pushed out).
 *   H5  Same filesystem only: remember the root's st_dev, and skip any
 *       directory whose st_dev differs.
 *   H6  An unreadable directory: print a warning and CARRY ON. One
 *       locked folder shouldn't kill the whole scan.
 *
 * BONUS    per-subdirectory totals: walk() can RETURN the bytes under it.
 *          The top-level loop records each child's return value.
 *          Or look at nftw(3), which is libc's built-in tree walker.
 */
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_TOP 100

struct entry {
    long long size;
    char path[PATH_MAX];
};

static struct entry top[MAX_TOP];
static int top_n = 10;              /* how many to keep (from argv) */
static int top_used = 0;            /* how many slots are filled    */
static long long total_bytes = 0;
static long long total_files = 0;

/* Offer one file to the top-N list. */
static void consider(const char *path, long long size)
{
    /* TODO: see H3 */
    (void)path;
    (void)size;
}

/* Returns the number of bytes under path. */
static long long walk(const char *path)
{
    /* TODO: see H1, H2, H6. Update total_bytes/total_files, call consider(). */
    (void)path;
    (void)consider;   /* delete once walk() calls it */
    return 0;
}

int main(int argc, char **argv)
{
    const char *dir = argc >= 2 ? argv[1] : getenv("HOME");
    if (argc >= 3)
        top_n = atoi(argv[2]);      /* THINK: what does atoi("ten") return? */
    if (top_n < 1 || top_n > MAX_TOP)
        top_n = 10;

    walk(dir);

    printf("== biggest files\n");
    for (int i = 0; i < top_used; i++)
        printf("%12lld  %s\n", top[i].size, top[i].path);   /* TODO: human sizes (lesson 11) */

    printf("total: %lld bytes in %lld files\n", total_bytes, total_files);
    return 0;
}
