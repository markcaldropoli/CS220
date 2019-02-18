#include <stdio.h>
#include <unistd.h>

int main() {
	printf("My pid is %d, parent pid is %d.\n", getpid(), getppid());
	return 0;
}
