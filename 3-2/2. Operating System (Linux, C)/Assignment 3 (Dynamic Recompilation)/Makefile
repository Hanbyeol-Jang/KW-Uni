default:
	gcc -c D_recompile_test.c
	gcc -o D_recompile_test D_recompile_test.c
	gcc -o D_recompile D_recompile.c -lrt
	objdump -d D_recompile_test.o > test

dynamic:
	gcc -c D_recompile_test.c
	gcc -o D_recompile_test D_recompile_test.c
	gcc -Ddynamic -o D_recompile D_recompile.c -lrt
	objdump -d D_recompile_test.o > test

clean:
	$(RM) D_recompile_test D_recompile_test.o 
	$(RM) D_recompile D_recompile.o
	$(RM) test
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches
