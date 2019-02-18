#include <shared.h>

int main() {
	void *p;
	p = logger_malloc(10 * sizeof(unsigned int));
	logger_free(p);
	return 0;
}
