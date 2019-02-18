# OPTIONAL: Set these variables as required.
CFLAGS := -g -Wall -std=c99
LDFLAGS :=
LDLIBS :=

all: static-driver

# OPTIONAL: COMPLETE THIS TARGET
# This target produces an object file for making libraries.
parser.o : parser.c
	gcc -o parser.o -c parser.c

# COMPLETE THIS TARGET
# This target produces the dynamic library.
lib/libparser.so: parser.o driver.c
	gcc -g -fPIC -Wall parser.c -shared -o lib/libparser.so

# COMPLETE THIS TARGET
# This target produces the executable using the dynamic library
driver: driver.c lib/libparser.so
	gcc -g -Wall -o driver driver.c lib/libparser.so

# This target produces the executable using static library
static-driver: driver.c lib/libparser.a
	$(CC) $(CFLAGS) driver.c -I$PWD lib/libparser.a -o static-driver

.PHONY: clean
clean:
	rm -fv static-driver driver
	rm -fv lib/libparser.so
	rm -fv *.o *.txt *.bin
	rm -fv *~ \#*\# *.swp


# Add testing targets. See the file.
# Doesn't currently do anything.
include test.make
