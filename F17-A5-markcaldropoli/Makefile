all: main

main: main.c node.c
	gcc -o main main.c node.c

.PHONY: clean
clean:
	rm -fv main *.o
	rm -fv *~ \#*\# *.swp

# Rule to build a test executable
# DO NOT MODIFY
test: test.c node.c
	$(eval CFLAGS+=-g -Wall -std=c99)
	$(eval LDFLAGS+=-lm -lcunit)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to run the test executable
# DO NOT MODIFY
.PHONY: test-run
test-run: test
	{ whoami && date && ./test ; } >> test_results.txt

# Rule to run your clean rule
# AND remove the test executable
# AND output results
.PHONY: really-clean
really-clean: clean
	rm -fv test
