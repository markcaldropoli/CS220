#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_var = 0;

/* Each thread could get a different worker function or the same worker function could be used by multiple functions */
void *worker_function(void *payload) {
	/* Thread's code goes here */
	global_var++;
	printf("%d\n", global_var);
	printf("In thread %d\n", (int) payload);
}

#define NUM_THREADS 3

int main() {
	pthread_t threads [NUM_THREADS];
	int i;

	/* Declare payload here */
	void *payload;

	for(i = 0; i < NUM_THREADS; i++) {
		sleep(2);
		printf("-----\n");
		pthread_create(&threads[i], NULL, worker_function, (void *) payload);
	}
	sleep(2);
	printf("-----\n\n");
	printf("In main thread\n");
	void *ptr = (void *) malloc (sizeof(void *));

	for(i = 0; i < NUM_THREADS; i++) {
		sleep(2);
		printf("-----\n");
		printf("worker %d\n", i);
		worker_function(ptr);
		printf("------\n");
		sleep(2);
		printf("main %d\n", i);
		pthread_join(threads[i], NULL);
	}
	printf("-----\n");

	printf("Exiting main thread\n");
	pthread_exit(NULL);
	return(0);
}
