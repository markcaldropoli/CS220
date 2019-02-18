#include "functions.h"

int cryptic_calculator(void *payload) {
	char op;
	short b3, b5, b7;

	op = *((char *)(payload));
	b3 = *((short *)(payload + 2));
	b5 = *((short *)(payload + 4));
	b7 = *((short *)(payload + 6));

	if(op == '*') return b3*b5*b7;
	else if(op == '/' && b3 != 0) return b5/b3;
	return 0xBAD;
}

void my_memcpy(void *dst, void *src, unsigned int num_bytes) {
	int i;

	i = 0;
	while(i < num_bytes) {
		*((char *)(dst+i)) = *((char *)(src+i)); 
		i++;
	}
	dst -= i;
}

void swap_strs(char *s1, char *s2) {
	char arr[500];
	char *t = arr;
	int count = 0;

	while(*s1) {
		arr[count] = *s1++;
		count++;
	}

	s1 -= count;

	while(*s2) {
		s1[0] = s2[0];
		s2[0] = t[0];
		*s1++, *s2++, *t++;
	}
}
