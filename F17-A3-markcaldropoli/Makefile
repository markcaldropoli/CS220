all: main

main: main.c impl.c
	gcc main.c impl.c -lm -o main

.PHONY: clean
	rm -fv main *.o
	rm -fv *~ \#*\# *.swp

# Rule to build a test executable
# DO NOT MODIFY
test: test.c functions.c
	$(CC) $(CFLAGS) $^ -o $@

# Rule to run a testing script and produce an output file
# DO NOT MODIFY
.PHONY: test-run
test-run: test test.py
	python3 test.py

# Rule to run *your* clean rule AND remove the test executable
# DO NOT MODIFY
.PHONY: really-clean
really-clean: clean
	rm -fv test
