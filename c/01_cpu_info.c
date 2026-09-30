/*
 * 01 — CPU info            (same goal as sh/01_cpu_info.sh — do that first)
 *
 * GOAL     Print the CPU model name, the number of logical CPUs, and each
 *          CPU's current MHz.
 *
 * NEW IN C fopen / fgets / fclose   read a text file one line at a time
 *          strncmp                  "does this line start with X?"
 *          strchr / strcspn         find a character / find the end of a line
 *          perror                   print WHY something failed (errno)
 *
 * CHECK    lscpu ; nproc ; your sh version (same numbers?)
 *
 * HINTS
 *   H1  fgets() reads ONE line, INCLUDING its '\n', into a buffer you own.
 *   H2  Lines look like "key\t: value\n". strchr(line, ':') finds the colon.
 *       The value starts one or two chars after it.
 *   H3  line[strcspn(line, "\n")] = '\0';   <- read this until it makes sense.
 *   H4  strncmp(line, "processor", 9) == 0 means "starts with processor".
 *       Counting the 9 by hand is error-prone. What is sizeof "processor" - 1?
 *   H5  "model" matches two different keys. Match more of the key.
 *
 * BONUS    sysconf(_SC_NPROCESSORS_ONLN) (unistd.h) is the libc way to count
 *          CPUs. Does it agree with your count? (strace it: what does it read?)
 */
#include <stdio.h>
#include <string.h>

/* Given "key\t: value\n", return a pointer to "value" (newline removed).
 * Modifies line in place. Returns NULL if there is no ':'. */
static char *value_of(char *line)
{
    /* TODO: find ':' → step past it and the space → chop the '\n' */
    (void)line;
    return NULL;
}

int main(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) {
        perror("/proc/cpuinfo");
        return 1;
    }

    char line[512];
    char model[256] = "TODO";
    int cpus = 0;

    while (fgets(line, sizeof line, f)) {
        /* TODO 1: "model name" line, first one only → copy the value into model.
         *         Use snprintf(model, sizeof model, "%s", ...), not strcpy. Why? */

        /* TODO 2: "processor" line → count it */

        /* TODO 3: "cpu MHz" line → printf("cpu %d : %s MHz\n", ?, value)
         *         Which CPU is this? What have you counted so far? */
    }
    fclose(f);
    (void)value_of;   /* delete once you call it */

    printf("Model : %s\n", model);
    printf("CPUs  : %d\n", cpus);
    return 0;
}
