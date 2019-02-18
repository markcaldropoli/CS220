#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define LOOPS ((unsigned int) 0xffffffff)
#define TRIALS 10

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1) {
	long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

	return (diff<0);
}

void timeval_print(char *str, struct timeval *tv) {
	printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

int main() {
	struct timeval tvDiff, tvStart, tvEnd; /* Time values to calculate time taken */
	int i, j; /* Integers for iterations */
	long long hundred = 0, zero = 0, result = 0;

	for(i = 0; i < TRIALS; i++) {
		/* Record Values for NOP & RET */
		gettimeofday(&tvStart, NULL); /* Set Start Time */
		for(j = 0; j < LOOPS; j++) oneHundredNOP(); /* Run Assembly Code */
		gettimeofday(&tvEnd, NULL); /* Set End Time */

		timeval_subtract(&tvDiff, &tvEnd, &tvStart); /* Compute Difference */
		hundred = tvDiff.tv_sec*1000000 + tvDiff.tv_usec;

		/* Record Values for ONLY RET */
		gettimeofday(&tvStart, NULL); /* Set Start Time */
		for(j = 0; j < LOOPS; j++) zeroNOP(); /* Run Assembly Code */
		gettimeofday(&tvEnd, NULL); /* Sent End Time */

		timeval_subtract(&tvDiff, &tvEnd, &tvStart); /* Compute Difference */
		zero = tvDiff.tv_sec*1000000 + tvDiff.tv_usec;
	}

	hundred /= TRIALS;
	zero /= TRIALS;
	result = hundred - zero;

	printf("Average # of nop's per second: %'llu\n", LOOPS*100000000LL/result);

	return 0;
}
