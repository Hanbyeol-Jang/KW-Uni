OBJS1 = proxy_cache.c
EXEC1 = proxy_cache

CACHE = ~/cache/
CFLAGS = -g
CC = gcc

all:
	$(CC) -o $(EXEC1) $(OBJS1) -lcrypto
	
clean:
	rm -rf $(EXEC1)
	rm -rf $(CACHE)
	rm -rf ~/logfile
