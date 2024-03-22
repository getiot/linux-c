CC := gcc
CFLAGS := -std=gnu17 -Wall -Wextra
SRCS := $(wildcard *.c)
EXES := $(SRCS:.c=)

all: $(EXES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXES)

.PHONY: all clean
