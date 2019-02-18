CFLAGS := -std=c89 -g

prelim: prelim.c
	gcc -o prelim prelim.c -m32

ret2libc: ret2libc.c get_ebp.S
	$(CC) $(CFLAGS) -o ret2libc ret2libc.c get_ebp.S -m32

clean:
	rm -fv prelim
	rm -fv ret2libc
	rm -fv *.o *~ \#*\# *.swp
