CC     ?= cc
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -g -O0 -D_DEFAULT_SOURCE

SRCS := $(wildcard [0-9][0-9]_*.c)
BINS := $(SRCS:%.c=bin/%)

all: $(BINS)

bin/%: %.c | bin
	$(CC) $(CFLAGS) -o $@ $<

bin:
	mkdir -p bin

# make run-03_battery  → build + run one lesson
run-%: bin/%
	./bin/$*

clean:
	rm -rf bin

.PHONY: all clean
