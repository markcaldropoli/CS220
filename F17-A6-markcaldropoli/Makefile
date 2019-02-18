CFLAGS:= -g -Wall

all: file_recognizer

file_recognizer: file_recognizer.c
	$(CC) $(CFLAGS) -o file_recognizer file_recognizer.c

.PHONY: clean
clean:
	rm -fv file_recognizer
	rm -fv *.o *~ \#*\# *.swp

# test.make contains the test suite for grading.
# We will provide it then. For now, it doesn't do much.
include test.make
