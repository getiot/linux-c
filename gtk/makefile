CFLAGS=`pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`

# gcc gtk-test.c $(pkg-config --cflags --libs gtk+-3.0) -o gtk-test
# gcc $(pkg-config --cflags gtk+-2.0) gtk-test.c -o gtk-test $(pkg-config --libs gtk+-2.0)

all:
	gcc ${CFLAGS} gtk-test.c ${LIBS} -o gtk-test

clean:
	rm gtk-test