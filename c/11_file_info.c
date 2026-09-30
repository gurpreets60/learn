/*
 * 11 — File info           (same goal as sh/11_file_info.sh)
 *
 * NEW IN C lstat(2) / struct stat   the inode's metadata
 *          S_ISDIR, S_ISLNK ...     decode st_mode's TYPE bits
 *          st_mode & 0777           the PERMISSION bits (octal!)
 *          getpwuid / getgrgid      uid number → "root"
 *          strftime                 time_t → "2026-09-12 10:31"
 *          readlink(2)              where does a symlink point?
 *
 * CHECK    ls -ld PATH ; stat PATH ; your sh version
 *
 * HINTS
 *   H1  stat() follows symlinks and lstat() doesn't. Which one lets you
 *       SEE a symlink?
 *   H2  The rwx string, one bit at a time:
 *           (m & S_IRUSR) ? 'r' : '-'    then S_IWUSR, S_IXUSR, S_IRGRP ...
 *       Nine checks, or a loop over "rwxrwxrwx" and a bit mask that shifts
 *       right each time (0400 >> i).
 *   H3  printf("%03o", m & 0777) prints 644. Why %o?
 *   H4  readlink does NOT add a '\0'. It returns the length. You terminate
 *       the string yourself.
 *   H5  localtime(&st.st_mtime) → struct tm*, then
 *       strftime(buf, sizeof buf, "%F %H:%M", tm).
 *   H6  getpwuid can return NULL (the user was deleted). Print the number.
 */
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

static const char *type_name(mode_t m)
{
    /* TODO: S_ISREG → "regular file", S_ISDIR, S_ISLNK, S_ISCHR ("char device"),
     *       S_ISBLK, S_ISFIFO, S_ISSOCK */
    (void)m;
    return "TODO";
}

/* Fill out[11] with something like "-rw-r--r--". */
static void perm_string(mode_t m, char out[11])
{
    /* TODO: out[0] = type char ('-', 'd', 'l', 'c', ...), then 9 rwx chars */
    (void)m;
    snprintf(out, 11, "??????????");
}

/* 3000 → "2.9 KiB" */
static void human_size(off_t bytes, char *out, size_t n)
{
    /* TODO: divide by 1024 while it's >= 1024, counting the steps */
    snprintf(out, n, "%lld B", (long long)bytes);
}

static void show(const char *path)
{
    struct stat st;
    printf("%s\n", path);
    /* TODO: lstat (perror + return on failure) */
    (void)st;

    /* TODO: print type, perms (+ octal), owner:group, size, changed
     *       if it's a symlink: readlink and print "→ target" */
    (void)type_name;
    (void)perm_string;
    (void)human_size;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s PATH...\n", argv[0]);
        return 2;
    }
    for (int i = 1; i < argc; i++)
        show(argv[i]);
    return 0;
}
