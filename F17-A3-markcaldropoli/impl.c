#include "define.h"
#include <math.h>

float distance(struct point p1, struct point p2) {
	float x = pow(p1.x - p2.x, 2);
	float y = pow(p1.y - p2.y, 2);
	float z = pow(p1.z - p2.z, 2);
	float sum = x + y + z;
	return sqrt(sum);
}

int strrindex(char s[], char t[]) {
	int slen, tlen, i, j, count, roccur;

	for(slen = 0; s[slen] != '\0'; slen++);
	for(tlen = 0; t[tlen] != '\0'; tlen++);

	if(tlen > slen) return -1;

	if(slen == tlen) {
		i = 0;
		while(i < slen) {
			if(s[i] != t[i]) return -1;
			i++;
		}
		return 0;
	}

	roccur = -1;
	count = 0;
	for(i = 0; i < slen; i++) {
		for(j = 0; j < tlen; j++) {
			if(s[i] != t[j]) {
				break;
			} else if((slen-i == tlen) && (slen/2 != tlen) && (s[i] == s[i+1])) {
				i+=slen-i;
			} else {
				i++;
				count++;
			}
			if(j == tlen-1) {
				roccur = i-tlen;
				i-=count;
				count = 0;
			}
		}
	}
	return roccur;
}

int is_int(char str[]) {
	int i = 0;
	if(str[0] == '-' || (str[0] >= '0' && str[0] <= '9')) {
		for(i = 1; str[i] != '\0'; i++) {
			if(str[i] < '0' || str[i] > '9') {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

