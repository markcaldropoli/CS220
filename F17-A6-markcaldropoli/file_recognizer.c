#include "file_recognizer.h"
#include <stdio.h>

int signatureType(unsigned char signature[]) {
	/* If GIF return 1 */
	if(signature[0] == 0x47 && signature[1] == 0x49 && signature[2] == 0x46 && signature[3] == 0x38 
	   && (signature[4] == 0x39 || signature[4] == 0x37) && signature[5] == 0x61) {
		return 1;
	}

	/* If ELF return 2 */
	if(signature[0] == 0x7f && signature[1] == 0x45 && signature[2] == 0x4C && signature[3] == 0x46) {
		return 2;
	}

	/* If PDF return 3 */
	if(signature[0] == 0x25 && signature[1] == 0x50 && signature[2] == 0x44 && signature[3] == 0x46) {
		return 3;
	}
	
	/* If ZIP return 4 */
	if(signature[0] == 0x50 && signature[1] == 0x4B) {
		return 4;
	}

	/* If Java class return 5 */
	if(signature[0] == 0xCA && signature[1] == 0xFE && signature[2] == 0xBA && signature[3] == 0xBE) {
		return 5;
	}

	/* If PNG return 6 */
	if(signature[0] == 0x89 && signature[1] == 0x50 && signature[2] == 0x4E && signature[3] == 0x47
	   && signature[4] == 0x0D && signature[5] == 0x0A && signature[6] == 0x1A && signature[7] == 0x0A) {
		return 6;
	}

	/* Otherwise unknown, return -1 */
	return -1;
}

int main(int argc, char const *argv[]) {
	FILE *fp;
	int i;
	unsigned char signature[8];

	if(argc != 2) {
		puts("Invalid input.");
		return -1;
	}

	char const *file = argv[1];
	fp = fopen(file, "r");

	if(fp == NULL) {
		puts("Invalid input.");
		return -1;
	}

	for(i = 0; i < sizeof(signature); i++) fscanf(fp, "%c", &signature[i]);
	fclose(fp);

	int fileType = signatureType(signature);

	switch(fileType) {
		case 1: puts("This is a GIF file."); break;
		case 2: puts("This is an ELF file."); break;
		case 3: puts("This is a PDF file."); break;
		case 4: puts("This is a ZIP file."); break;
		case 5: puts("This is a Java class file."); break;
		case 6: puts("This is a PNG file."); break;
		default: puts("File type unknown.");
	}
	return 0;
}
