CC ?= gcc

LFLAGS = -lpaho-mqtt3c -lpaho-mqtt3a

all:
	$(CC) MQTTClient_publish.c -o MQTTClient_publish $(LFLAGS)
	$(CC) MQTTClient_subscribe.c -o MQTTClient_subscribe $(LFLAGS)

.PHONY: clean
clean:
	rm MQTTClient_publish MQTTClient_subscribe
