#include "bits.c"
#include <stdio.h>

int main() {
	printf("Test print_in_binary\n");
	print_in_binary(1);
	print_in_binary(4);
	print_in_binary(32);

	printf("\nTest Macros\n");
	int x = 2;
	print_in_binary(x);
	print_in_binary(BIT(x));
	print_in_binary(BIT_SET(x, 32));
	print_in_binary(BIT_CLEAR(x, 2));
	print_in_binary(BIT_FLIP(x, 2));
	print_in_binary(IS_SET_ANY(x, 2));
	print_in_binary(IS_SET_ANY(x, 64));
	print_in_binary(x);
	print_in_binary(IS_CLEAR_ANY(x, 2));
	print_in_binary(IS_CLEAR_ANY(x, 64));

	printf("\nTest Functions\n");
	printf("0x%X\n", get_page_offset(0xf712c0d0));
	printf("0x%X\n", get_tlb_id(0xf712c0d0));
	printf("0x%X\n", get_tlb_tag(0xf712c0d0));
	printf("0x%X\n", set_page_offset(0xf712c0d0, 0x1a3));
	printf("0x%X\n", set_tlb_id(0xf712c0d0, 0x0));
	printf("0x%X\n", set_tlb_tag(0xf712c0d0, 0x8400));

	return 0;
}
