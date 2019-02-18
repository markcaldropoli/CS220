all:
	$(info use `make loop` or `make buggy`.)

loop: loop.c
	gcc loop.c -o loop

buggy: buggy.c
	gcc -std=c89 -fno-stack-protector -w -g -o buggy buggy.c

.PHONY: clean
clean:
	rm -fv loop buggy
	rm -fv *~ #*#
