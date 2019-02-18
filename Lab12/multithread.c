#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
char global_char[100];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *scan_worker(void *payload) {
	pthread_mutex_lock(&m);
	scanf("%s", global_char);
	pthread_mutex_unlock(&m);
}

void *print_worker(void *payload) {
	pthread_mutex_lock(&m);
	printf("%s\n", global_char);
	pthread_mutex_unlock(&m);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int i;

	pthread_create(&threads[0], NULL, scan_worker, NULL);
	pthread_create(&threads[1], NULL, print_worker, NULL);

	printf("Main Thread\n");
	for(i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("Exiting Main Thread\n");
	pthread_exit(NULL);
	return 0;
}
