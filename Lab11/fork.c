#include <stdio.h>
#include <unistd.h>

int main() {
	int x = 1;
	pid_t pid;
	pid = fork();

	if(pid == 0) {
		x++;
		printf("In child\n");
		printf("x == %d\n", x);
		printf("Child pid == %d\n", getpid());
		printf("Parent pid == %d\n", getppid());
	} else {
		x--;
		sleep(1);
		printf("In parent\n");
		printf("x == %d\n", x);
		printf("Child pid == %d\n", pid);
		printf("Parent pid == %d\n", getppid());
	}

	return 0;
}
