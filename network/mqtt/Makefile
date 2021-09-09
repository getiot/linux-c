CC ?= gcc

LFLAGS = -lpaho-mqtt3c -lpaho-mqtt3a

all:
	$(CC) MQTTClient_publish.c -o MQTTClient_publish $(LFLAGS)

.PHONY: clean
clean:
	rm MQTTClient_publish
