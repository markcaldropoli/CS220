#ifndef _MACROS_H
#define _MACROS_H

#define BIT(n) (1 << (n))
#define BIT_SET(v, mask) (v |= (mask))
#define BIT_MASK(len) (BIT(len) - 1)
#define TEST_IF_ANY_SET(v, start, end) ((((v) >> (start)) & (BIT_MASK((end)-(start)+1))) > 0)
#define TEST_IF_ALL_SET(v, start, end) ((((v) >> (start)) & (BIT_MASK((end)-(start)+1)) ^ BIT_MASK((end)-(start)+1)) == 0)

#endif
