all: loader hellosh

loader: loader.c
	gcc -o loader -Wl,-z,execstack loader.c -m32

hellosh: hellosh.c
	gcc -o hellosh hellosh.c

.PHONY: clean
clean:
	rm -f loader hellosh
	rm -f *.o
	rm -f *~ \#*\# *.swp
