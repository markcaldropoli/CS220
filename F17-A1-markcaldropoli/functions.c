#include "functions.h"

int isFib(unsigned long i) {
    int n1 = 0;
    int n2 = 1;
    int n = 3;

    if(i == 1) return 2;

    while((n1+n2) != i && (n1+n2)<i) {
        int temp = n1+n2;
        n1 = n2;
        n2 = temp;
        n++;
    }

    if((n1+n2) == i) return n;
    return -1;
}

unsigned int count_vowels(unsigned long num) {
    int ones, tens, hundreds, thousands, millions;
    int count = 0;

    if(num > 1000000000) return 0;
    if(num == 0) return 2;

    ones = num % 10;
    tens = (num % 100)/10;
    hundreds = (num % 1000)/100;
    thousands = (num % 1000000)/1000;
    millions = num / 1000000;

    /* Number of vowels in #s 0-9 */
    int zeroToNine[] = {0,2,1,2,2,2,1,2,2,2};

    /* Number of vowels in #s 10-19 */
    int teens[] = {1,3,2,3,4,3,3,4,4,4};

    /* Number of vowels in #s 0,10,20,30,40,50,60,70,80,90 */
    int multOfTen[] = {0,1,1,1,1,1,1,2,2,2};

    if(tens == 1) count += teens[ones];
    else count += multOfTen[tens] + zeroToNine[ones];

    if(hundreds != 0) count += zeroToNine[hundreds] + 2;
    if(thousands != 0) count += zeroToNine[thousands] + 3;
    if(millions != 0) count += zeroToNine[millions] + 3;

    return count;
}

unsigned int count_ones(long n) {
    int count = 0;
    while(n != 0) {
        if(n % 2 == 1) count++;
        n /= 2;
    }
    return count;
}

unsigned long swap_bytes(unsigned long n) {
    unsigned long byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8;
    byte1 = (0xFF00000000000000 & n);
    byte2 = (0x00FF000000000000 & n);
    byte3 = (0x0000FF0000000000 & n);
    byte4 = (0x000000FF00000000 & n);
    byte5 = (0x00000000FF000000 & n);
    byte6 = (0x0000000000FF0000 & n);
    byte7 = (0x000000000000FF00 & n);
    byte8 = (0x00000000000000FF & n);

    byte1 = byte1 >> 8;
    byte2 = byte2 << 8;
    byte3 = byte3 >> 8;
    byte4 = byte4 << 8;
    byte5 = byte5 >> 8;
    byte6 = byte6 << 8;
    byte7 = byte7 >> 8;
    byte8 = byte8 << 8;

    return (byte1 + byte2 + byte3 + byte4 + byte5 + byte6 + byte7 + byte8);
}

long a4_minus_b4(int a, int b) {
    return (a*a*a*a)-(b*b*b*b);
}
