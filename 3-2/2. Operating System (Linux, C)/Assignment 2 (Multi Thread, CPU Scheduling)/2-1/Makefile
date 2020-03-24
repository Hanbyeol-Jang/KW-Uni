OBJS1 = gen_file.c
OBJS2 = thread.c
EXEC1 = gen_file
EXEC2 = thread

CC = gcc


all:
	$(CC) -o $(EXEC1) $(OBJS1)
	$(CC) -o $(EXEC2) $(OBJS2) -pthread -lrt
	
clean:
	rm -rf $(EXEC1)
	rm -rf $(EXEC2)
	rm -rf temp.txt
	rm -rf tmp*
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches

