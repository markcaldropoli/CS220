#include <stdio.h>
#include <time.h>

void forLoop(unsigned int n) {
	unsigned int i;
	for(i = 0; i < n; i++)
		;
}

void whileLoop(unsigned int n) {
	while(n > 0)
		n--;
}

void doWhileLoop(unsigned int n) {
	do { n--; } while (n > 0);
}

int main()
{
    clock_t tic = clock();
    
    /* Call loop function here */
    forLoop(1000000000);
    
    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    tic = clock();
    
    /* Call loop function here */
    whileLoop(1000000000);
    
    toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    tic = clock();
    
    /* Call loop function here */
    doWhileLoop(1000000000);
    
    toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}
