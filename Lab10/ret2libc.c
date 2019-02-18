#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern uint32_t* get_ebp();

void ret2libc(int dummy) {
	uint32_t* curr_ebp = get_ebp();
	curr_ebp[2] = curr_ebp[1];
	curr_ebp[1] = &system;
	char *str = "/bin/bash";
	curr_ebp[3] = str;
}

void ret2libc_generic(char *cmd) {
	uint32_t* curr_ebp = get_ebp();
	curr_ebp[3] = cmd;
	curr_ebp[2] = curr_ebp[1];
	curr_ebp[1] = &system;
}

int main() {
	/*ret2libc(0);*/
	ret2libc_generic("/bin/bash");
	printf("Done!\n");
	return 0;
}
