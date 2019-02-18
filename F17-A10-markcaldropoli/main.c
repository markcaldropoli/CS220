#include <stdio.h>
#include "bt.h"

void baz() {
	print_backtrace(4);
}

void bar() {
	baz();
}

void foo() {
	bar();
}

int main(int argc, char* argv[]) {
	foo();
	return 0;
}
