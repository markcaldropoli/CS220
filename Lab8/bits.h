#define BIT(n)				(1 << (n))
#define BIT_SET(v, mask)		(v |= (mask))
#define BIT_CLEAR(v, mask)		(v &= ~(mask))
#define BIT_CLEAR2(v, mask)		(v ^= (mask))
#define BIT_FLIP(v, mask)		(v = ~(mask))
#define IS_SET_ANY(v, mask)		(v & (mask))
#define IS_CLEAR_ANY(v, mask)		(v & ~(mask))
#define BIT_MASK(len)			( BIT(len)-1 )
#define BF_MASK(start, len)		( BIT_MASK(len)<<(start) )
#define BF_PREP(x, start, len)		( ((x)&BIT_MASK(len)) << (start) )
#define BF_GET(y, start, len)		( ((y) >> (start)) & BIT_MASK(len))
#define BF_SET(y, x, start, len)	( ((y) & ~(BF_MASK(start, len))) | BF_PREP(x, start, len))

void print_in_binary(unsigned int x);
unsigned int get_page_offset(unsigned int address);
unsigned int get_tlb_id(unsigned int address);
unsigned int get_tlb_tag(unsigned int address);
unsigned int set_page_offset(unsigned int address, unsigned int new_offset);
unsigned int set_tlb_id(unsigned int address, unsigned int new_tlb_id);
unsigned int set_tlb_tag(unsigned int address, unsigned int new_tag);
