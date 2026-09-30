/*
 * 13 — Organize a folder by file type   (same goal as sh/13_organize.sh)
 *
 *   ./bin/13_organize DIR           dry run
 *   ./bin/13_organize DIR --doit    really move
 *
 * NEW IN C mkdir(2)         and its EEXIST error, which here is FINE
 *          rename(2)        what mv does when both paths are on one disk
 *          tolower          one char at a time (<ctype.h>)
 *          lookup tables    a struct array beats a big if/else chain
 *
 * CHECK    ls -R DIR before and after ; run twice (the 2nd run moves nothing)
 *
 * HINTS
 *   H1  strrchr(name, '.') finds the last dot. NULL means no extension.
 *       What about ".hidden", where the dot is at position 0?
 *   H2  Look the extension up by looping over rules[] with strcmp. Lowercase
 *       a copy of the extension first.
 *   H3  mkdir(path, 0755) fails with errno == EEXIST if the folder is
 *       already there. That's not a real error, so ignore just that one.
 *   H4  rename() OVERWRITES an existing destination without asking! Check
 *       access(dest, F_OK) == 0 first. (There's a tiny race window. The
 *       fully safe version is renameat2 with RENAME_NOREPLACE, a bonus.)
 *   H5  rename fails with EXDEV across filesystems. mv copies + deletes
 *       in that case. Not needed here, since we move within one folder.
 *   H6  Skip anything that isn't S_ISREG. Use lstat, since symlinks
 *       count as "not regular".
 */
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct rule {
    const char *ext;
    const char *folder;
};

static const struct rule rules[] = {
    { "jpg", "images" }, { "jpeg", "images" }, { "png", "images" },
    /* TODO: the rest of the table from the sh version */
};
static const size_t n_rules = sizeof rules / sizeof rules[0];   /* why does this work? */

static const char *category(const char *name)
{
    /* TODO: H1, H2 */
    (void)name;
    (void)n_rules;
    return "other";
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s DIR [--doit]\n", argv[0]);
        return 2;
    }
    const char *dir = argv[1];
    int doit = argc >= 3 && strcmp(argv[2], "--doit") == 0;

    DIR *d = opendir(dir);
    if (!d) {
        perror(dir);
        return 1;
    }
    struct dirent *e;
    while ((e = readdir(d))) {
        /* TODO: build src path, lstat, skip non-regular (H6)
         *       folder = category(e->d_name); dest = dir/folder/name
         *       exists → print "skip"; dry → print "would move"; doit → mkdir + rename */
        (void)category;
    }
    closedir(d);

    if (!doit)
        printf("(dry run — add --doit to move files)\n");
    return 0;
}
