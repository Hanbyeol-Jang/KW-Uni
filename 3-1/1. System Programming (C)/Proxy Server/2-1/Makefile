OBJS1 = server.c
OBJS2 = client.c
EXEC1 = Server
EXEC2 = Client

CACHE = ~/cache/
CFLAGS = -g
CC = gcc

all:
	$(CC) -o $(EXEC1) $(OBJS1) -lcrypto
	$(CC) -o $(EXEC2) $(OBJS2) -lcrypto
	
clean:
	rm -rf $(EXEC1)
	rm -rf $(EXEC2)
	rm -rf $(CACHE)
	rm -rf ~/logfile
