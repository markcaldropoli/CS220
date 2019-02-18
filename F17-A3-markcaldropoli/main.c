#include "define.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	/* Test distance */
	printf("----- distance -----\n");

	struct point p1 = {.x = 1, .y = 2, .z = 3};
	struct point p2 = {.x = 7, .y = 8, .z = 9};
	struct point p3 = {.x = 32, .y = 12, .z = 39};

	printf("(1,2,3) <--> (7,8,9) == %f\n", distance(p1, p2));
	printf("(1,2,3) <--> (32,12,39) == %f\n", distance(p1, p3));
	/* Test strrindex */
	printf("----- strrindex -----\n");

	char s1[] = "equal";
	char s2[] = "equal";
	char s3[] = "not equal";
	char s4[] = "not equal not equal";
	char s5[] = "eeeeeee";
	char s6[] = "e";
	char s7[] = "ee";
	char s8[] = "eee";
	char s9[] = "eeee";
	char s10[] = "z";

	printf("\"equal\", \"equal\" == %d\n", strrindex(s1, s2));
	printf("\"equal\", \"not equal\" == %d\n", strrindex(s1, s3));
	printf("\"not equal\", \"equal\" == %d\n", strrindex(s3, s1));
	printf("\"not equal not equal\", \"equal\" == %d\n", strrindex(s4, s1));
	printf("\"eeeeeee\", \"e\" == %d\n", strrindex(s5, s6));
	printf("\"eeeeeee\", \"ee\" == %d\n", strrindex(s5, s7));
	printf("\"eeeeeee\", \"eee\" == %d\n", strrindex(s5, s8));
	printf("\"eeeeeee\", \"eeee\" == %d\n", strrindex(s5, s9));
	printf("\"not equal not equal\", \"z\" == %d\n", strrindex(s4, s10));

	/* Test is_int */
	printf("----- is_int -----\n");

	char sp[] = "567";
	char sn[] = "-567";
	char bil[] = "3000000000";
	char dn[] = "--567";
	char ws[] = "five hundred sixty seven";
	char d[] = "567.0";

	printf("\"567\" == %d\n", is_int(sp));
	printf("\"-567\" == %d\n", is_int(sn));
	printf("\"3000000000\" == %d\n", is_int(bil));
	printf("\"--567\" == %d\n", is_int(dn));
	printf("\"five hundred sixty seven\" == %d\n", is_int(ws));
	printf("\"567.0\" == %d\n", is_int(d));
	return 0;
}
