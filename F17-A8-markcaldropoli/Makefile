CFLAGS := -std=c89 -g

all: estimator

estimator: estimator.c estimator.S
	$(CC) $(CFLAGS) -o estimator estimator.c estimator.S

.PHONY: clean
clean:

include test.make
