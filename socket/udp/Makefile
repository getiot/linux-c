all:
	gcc udp_client.c -o udp_client
	gcc udp_server.c -o udp_server
	gcc udp_echo_server.c -o udp_echo_server
	gcc udp_broadcast_client.c -o udp_broadcast_client
	gcc udp_broadcast_server.c -o udp_broadcast_server

.PHONY: clean
clean:
	rm udp_client udp_server udp_echo_server
	rm udp_broadcast_client udp_broadcast_server
