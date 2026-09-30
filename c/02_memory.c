/*
 * 02 — Memory              (same goal as sh/02_memory.sh)
 *
 * GOAL     Total and available RAM in MiB, and the % in use. Bonus: swap.
 *
 * NEW IN C sscanf          pull typed values out of a string in one call
 *          unsigned long   sizes are big and never negative → %lu
 *          strcmp          whole-string equality (== compares POINTERS!)
 *
 * CHECK    free -m ; your sh version
 *
 * HINTS
 *   H1  Each line is "Key:      12345 kB". %s stops at whitespace, so it
 *       would grab "Key:" with the colon attached. Is that a problem?
 *       Could you just compare against "MemTotal:"?
 *   H2  Or use a scanset: %63[^:] means "up to 63 chars that aren't ':'".
 *       Then match the ':' literally in the format. Why 63 and not 64?
 *   H3  sscanf RETURNS how many fields it filled. Check it == 2.
 *   H4  used*100/total has the same integer trap as sh. Or use (double).
 */
#include <stdio.h>
#include <string.h>

/* Look up one key in /proc/meminfo. Returns its value in kB, 0 if not found. */
static unsigned long meminfo_kb(const char *key)
{
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) {
        perror("/proc/meminfo");
        return 0;
    }

    char line[256];
    unsigned long found = 0;
    while (fgets(line, sizeof line, f)) {
        /* TODO: parse the name and number out of line.
         *       If the name matches key: keep the number, stop looping. */
        (void)key;
    }
    fclose(f);
    return found;
}

int main(void)
{
    unsigned long total = meminfo_kb("MemTotal");
    unsigned long avail = meminfo_kb("MemAvailable");

    /* TODO: used, and percent used. What if total is 0? */
    unsigned long used = 0;
    double pct = 0.0;

    /* TODO: switch these to MiB */
    printf("Total     : %lu kB\n", total);
    printf("Available : %lu kB\n", avail);
    printf("Used      : %lu kB (%.0f%%)\n", used, pct);   /* why %% ? */

    /* THINK: this reopens the file once per key. Fine for two keys.
     *        How would you get many keys in ONE pass? */
    return 0;
}
