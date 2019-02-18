#include <stdio.h>

char gfoo[10000] = {0x10};

int main()
{
	printf("%p\n", &gfoo);
	return 0;
}
