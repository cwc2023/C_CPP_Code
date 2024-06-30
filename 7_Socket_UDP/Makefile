TARGET = udp_server udp_client

all:$(TARGET)

udp_server: udp_server.c
	gcc -Wall -g -o udp_server udp_server.c

udp_client: udp_client.c
	gcc -Wall -g -o udp_client udp_client.c

clean:
	rm -f $(TARGET)
.PHONY: all  clean
