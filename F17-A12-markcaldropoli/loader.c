/* loader.c */

/* TODO: Include appropriate headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	/* TODO: Declare an array large enough to hold the raw bytes. Raw bytes are best stored in byte-addressable arrays. Pick the appropriate type. Call it "raw_bytes"*/
	unsigned char raw_bytes[1024];
	int arg1, arg2, result;
	char op;
	FILE *fp;

	memset(&raw_bytes[0], 0, sizeof(raw_bytes));

	/* TODO: Declare a function pointer type that matches the calc function's type. Call it  "Calc_fptr" */
	typedef int (*Calc_fptr)(char, int, int);

	/* TODO if number of arguments is not 4 (5 including program name) */
	if(argc != 5) {
		printf("Usage %s <filename> <uint> <operation> <uint>\n", argv[0]);
		exit(1);
	}

	arg1 = atoi(argv[2]);
	arg2 = atoi(argv[4]);
	op = *argv[3];

	/* TODO: Open and read the binary file into raw_bytes. Use fopen and fread. */
	fp = fopen(argv[1], "rb");

	if(!fp) {
		printf("Invalid file entry.\n");
		exit(1);
	}

	fread(raw_bytes, sizeof(raw_bytes)*2, 1, fp);

	Calc_fptr calculator;
	calculator = (Calc_fptr) raw_bytes;
	result = calculator(op, arg1, arg2);
	/* TODO: Print the result. Refer to sample input and output. */
	printf("%d %c %d = %d\n", arg1, op, arg2, result);
	return 0;
}
