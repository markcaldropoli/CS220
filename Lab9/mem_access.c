#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <malloc.h>

#define STEP_SIZE	1024
#define READ_SIZE	(64*1024*1024)
#define PAGE_SIZE	4096
#define NG		1
#define PAGES_IN_NG	(NG*1024*1024)/PAGE_SIZE

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1) {
	long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

	return (diff<0);
}

void timeval_print(char *str, struct timeval *tv) {
	printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

void test_hdd() {
	struct timeval tvDiff, tvStart, tvEnd;
	int fd, i;
	char c[STEP_SIZE];

	fd = open("file64M", O_RDONLY);
	/* Start timer here */
	gettimeofday(&tvStart, NULL);
	for(i = 0; i < READ_SIZE; i+=STEP_SIZE) read(fd, &c[0], STEP_SIZE);
	/* Stop timer here */
	gettimeofday(&tvEnd, NULL);
	/* Calculate time taken here */
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("HDD ACCESS: ", &tvDiff);
}

void test_mem() {
	int i, j;
	struct timeval tvDiff, tvStart, tvEnd;
	unsigned char *mem_arr[PAGES_IN_NG];

	/* Allocate N GB on the heap */
	for(i = 0; i <PAGES_IN_NG; i++) {
		if((mem_arr[i] = memalign(PAGE_SIZE, PAGE_SIZE)) == NULL) {
			printf("Malloc failed...\n");
		}
	}

	/* Start timer */
	gettimeofday(&tvStart, NULL);
	for(i = 0; i < PAGES_IN_NG; i++)
		for(j = 0; j < PAGE_SIZE; j++)
			mem_arr[i][j]++;
	/* End timer */
	gettimeofday(&tvEnd, NULL);
	/* Calculate time taken */
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("MEM SERIAL ACCESS: ", &tvDiff);

	/* Start timer */
	gettimeofday(&tvStart, NULL);
	for(j = 0; j < PAGE_SIZE; j++)
		for(i = 0; i < PAGES_IN_NG; i++)
			mem_arr[i][j]++;
	/* End timer */
	gettimeofday(&tvEnd, NULL);
	/* Calculate time taken */
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("MEM PAGE STEP ACCESS: ", &tvDiff);
}

int main() {
	test_hdd();
	return 0;
}
