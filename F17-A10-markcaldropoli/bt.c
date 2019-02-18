#include <stdio.h>
#include <stdlib.h>

extern unsigned int* get_rbp();
extern int main();

void print_backtrace(int count) {
	unsigned char* start = (unsigned char*)(main);
	unsigned char* end = (unsigned char*)(start);
	while(*end != 0xc3) end++;

	unsigned int* rbp = get_rbp();

	while(count > 0) {
		unsigned int ret = *(rbp+1);
		printf("%x\n", ret);
		if(ret >= (unsigned int)start && ret <= (unsigned int)end) return;
		rbp = (unsigned int*)(*rbp);
		count--;
	}
}
