CFLAGS := -std=c89 -g
all: driver

driver: driver.c reverse64.S
	$(CC) $(CFLAGS) -o driver driver.c reverse64.S

.PHONY: clean
clean:
	rm -fv driver
	rm -fv *.o *~ \#*\# *.swp
