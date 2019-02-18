#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char const *argv[]) {
	/* Test cryptic_calculator */
	void *payload = malloc(8);
	*((char *)(payload)) = '*';
	*((short *)(payload + 2)) = 2;
	*((short *)(payload + 4)) = 2;
	*((short *)(payload + 6)) = 3;
	printf("2*2*3 == %d\n", cryptic_calculator(payload));

	*((char *)(payload)) = '/';
	printf("2/2 == %d\n", cryptic_calculator(payload));

	*((char *)(payload + 2)) = 0;
	printf("0xBAD == 0x%X\n", cryptic_calculator(payload));

	*((char *)(payload)) = '.';
	printf("0xBAD == 0x%X\n", cryptic_calculator(payload));

	/* Test my_memcpy */
	void *src = malloc(8);
	void *dst = malloc(8);
	unsigned int x = 3;
	*((char *)(src)) = 'A';
	*((char *)(src+1)) = 'B';
	*((char *)(src+2)) = 'C';
	printf("src == %s\n", src);
	my_memcpy(dst, src, x);
	printf("dst == %s\n", dst);

	/* Test swap_strs */
	char s1[] = "ABC";
	char s2[] = "DEF";
	char s3[] = "a";
	char s4[] = "b";
	char s5[] = "abcdefghijklmnopqrstuvwxyz";
	char s6[] = "zyxwvutsrqponmlkjihgfedcba";
	char *s1p, *s2p, *s3p, *s4p, *s5p, *s6p;
	s1p = s1;
	s2p = s2;
	s3p = s3;
	s4p = s4;
	s5p = s5;
	s6p = s6;
	swap_strs(s1p, s2p);
	swap_strs(s3p, s4p);
	swap_strs(s5p, s6p);
	printf("*s1 == %s\n", s1p);
	printf("*s2 == %s\n", s2p);
	printf("*s3 == %s\n", s3p);
	printf("*s4 == %s\n", s4p);
	printf("*s5 == %s\n", s5p);
	printf("*s6 == %s\n", s6p);
	return 0;
}
