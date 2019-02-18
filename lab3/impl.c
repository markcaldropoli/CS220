#include <stdio.h>

struct bad_struct {
	short s1;
	long l1;
	short s2;
};

struct good_struct {
	short s1;
	short s2;
	long l1;
};

union unit {
	char c;
	int i;
	long l;
};

unsigned int foo(int x[]) {
	return sizeof(x);
}

int main(int argc, char* argv[]) {
	struct good_struct gs;
	struct bad_struct bs;
	union unit u;
	int x[30];

	printf("Please input a long: ");
	scanf("%lu", &u.l);

	printf("sizeof(gs) == %d && sizeof(bs) == %d\n", sizeof(gs), sizeof(bs));
	printf("&gs == %p && &bs == %p\n", &gs, &bs);

	printf("sizeof(u) == %d\n", sizeof(u));
	printf("&u.c == %p && &u.i == %p && &u.l == %p\n", &u.c, &u.i, &u.l);

	printf("%d\n", (int) sizeof(u));
	printf("%c, %lu, %d, %s\n", u.c, u.l, u.i, &u.l);

	printf("sizeof(x) == %d\n", sizeof(x));
	printf("foo(x) == %d\n", foo(x));

	return 0;
}
