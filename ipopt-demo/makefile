CC = gcc
all:
	$(CC) client.c fun.c -o client
	$(CC) server.c fun.c -o server
.PHONY: all clean
clean:
	$(RM) client server $(TARGETS)
