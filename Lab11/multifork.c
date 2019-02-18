#include <stdio.h>
#include <unistd.h>

int main() {
	fork();
	printf("%d: %d: Line 1\n", getpid(), getppid());
	fork();
	printf("%d: %d: Line 2\n", getpid(), getppid());
	if(fork() == 0) printf("%d: %d: Line 3\n", getpid(), getppid());
	else printf("%d: %d: Line 4\n", getpid(), getppid());
	sleep(2);
	return 0;
}
