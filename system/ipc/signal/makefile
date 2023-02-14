CC ?= gcc

all:
	$(CC) simple_example.c -o simple_example
	$(CC) start_stop_signal.c -o start_stop_signal -pthread

.PHONY: clean
clean:
	rm simple_example
	rm start_stop_signal
