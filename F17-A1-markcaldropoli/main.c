#include <stdio.h>
#include "functions.h"

int main(int argc, char **argv) {
    /* Test #1 */
    printf("Test 1:\n");
    printf("%d\n", isFib(3));
    printf("%d\n", isFib(144));
    printf("%d\n", isFib(32));
    printf("%d\n", isFib(7));
    printf("%d\n", isFib(1));
    printf("%d\n", isFib(0));

    /* Test #2 */
    printf("\nTest 2:\n");
    printf("%u\n", count_vowels(342)); /* 6 */
    printf("%u\n", count_vowels(115)); /* 7 */
    printf("%u\n", count_vowels(1500)); /* 9 */
    printf("%u\n", count_vowels(27)); /* 3 */
    printf("%u\n", count_vowels(0)); /* 2 */
    printf("%u\n", count_vowels(10000000000)); /* 0 */

    /* Test #3 */
    printf("\nTest 3:\n");
    printf("%d\n", count_ones(5)); /* 2 */
    printf("%d\n", count_ones(32)); /* 1 */
    printf("%d\n", count_ones(37)); /* 3 */
    printf("%d\n", count_ones(63)); /* 6 */
    printf("%d\n", count_ones(-1));

    /* Test #4 */
    printf("\nTest 4:\n");
    printf("Original: 12345678deadbeef\n");
    printf("Output:   %lx\n", swap_bytes(0x12345678deadbeef));

    /* Test #5 */
    printf("\nTest 5:\n");
    printf("%ld\n", a4_minus_b4(5,3)); /* 544 */
    printf("%ld\n", a4_minus_b4(-5,-3)); /* 544 */
    printf("%ld\n", a4_minus_b4(50,7)); /* 6247599 */
    return 0;
}
