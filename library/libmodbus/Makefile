CC=gcc
CFLAGS=-I/usr/local/include/modbus/ -lmodbus -g

MASTER=modbus-rtu-master
SLAVE=modbus-rtu-slave

all:
	$(CC) -o $(MASTER) $(MASTER).c $(CFLAGS)
	$(CC) -o $(SLAVE) $(SLAVE).c $(CFLAGS)

clean:
	rm -rf $(MASTER) $(SLAVE)

