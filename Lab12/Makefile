all: multithread #worker mutex

#worker: worker.c
#	gcc -o worker worker.c -pthread

#mutex: mutex.c
#	gcc -o mutex mutex.c -pthread

multithread: multithread.c
	gcc -o multithread multithread.c -pthread

.PHONY: clean
clean:
	rm -fv worker *.o
	rm -fv mutex *.o
	rm -fv *~ \#*\# *.swp
