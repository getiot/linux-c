CFLAGS_DBUS = $(shell pkg-config --cflags --libs dbus-1)
CFLAGS_DBUS_GLIB = $(shell pkg-config --cflags --libs dbus-glib-1)
#CFLAGS_GIO  = $(shell pkg-config --cflags --libs gio-2.0)

CFLAGS = -g -Wall -Werror


all: dbus-server dbus-client

dbus-server: dbus-server.c
	gcc $< $(CFLAGS) $(CFLAGS_DBUS) $(CFLAGS_DBUS_GLIB) -o $@

dbus-client: dbus-client.c
	gcc $< $(CFLAGS) $(CFLAGS_DBUS) $(CFLAGS_DBUS_GLIB) -o $@

clean:
	rm -f dbus-server
	rm -f dbus-client


.PHONY: all clean