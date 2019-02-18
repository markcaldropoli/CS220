#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;
    for(x = 0; x < 100000000; x++) {
        int *p = (int *) malloc (x * 0x1000);
    }
    return 0;
}
