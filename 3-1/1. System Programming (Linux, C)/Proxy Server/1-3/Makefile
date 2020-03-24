OBJS = proxy_cache.c
EXEC = proxy_cache
CACHE = ~/cache/

CFLAGS = -g

CC = gcc

all:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -lcrypto

clean:
	rm -rf $(EXEC)
	rm -rf $(CACHE)
	rm -rf ~/logfile
