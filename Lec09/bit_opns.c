// CS 350, Fall 2013
//
// bit_opns.c:  Bit shifting and bitwise operations.
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>

main() {
	int v, i;  // value to shift, loop counter
#define NBR_SHIFTS 5

	// v << i yields the result of taking v and left-shifting it i bits.
	// The rightmost positions are filled in with zero bits.
	// Left shifting i bits corresponds to multiplying by 2^i.
	//
	printf("Left shifts:\n");
	v = 1;
	for (i = 0; i < NBR_SHIFTS; i++) {
		printf("%d << %2d = %d\n", v, i, v << i);
	}
	printf("\n");

	// v >> i yields the result of taking v and right-shifting it i bits.
	// If v >= 0 then v >> i == v/(2^i).  (I.e., right shifting
	// i bits corresponds to division by 2^i.)
	//
	printf("Right shifts on 2^30:\n");
	v = 1 << 30;     // 2^30 = 1073741824
	for (i = 0; i < NBR_SHIFTS; i++) {
		printf("%d >> %2d = %d\n", v, i, v >> i);
	}
	printf("\n");

	// If v < 0 then for right shifting to correspond to division, we
	// must shift 1 bits in from the right.
	//
	// The C standard is silent on whether the leftmost positions are
	// filled in with zero bits ("logical right shift") or with copies
	// of the sign bit ("arithmetic right shift").
	//
	printf("(Algebraic? Logical?) Right shifts on -2^31:\n");
	v = -1 << 31;   // -2^31 = -2147483648
	for (i = 0; i < NBR_SHIFTS; i++) {
		printf("%d >> %2d = %d\n", v, i, v >> i);
	}
	printf("\n");

	// Print result of some bitwise operations
	//
	printf("Some bitwise operations:\n");
	int x = 0x147ad036, y = 0x02468ace;
	printf("~%#010x = %#010x\n", x, ~x);
	printf("%#010x %s %#010x = %#010x\n", x, "&", y, x & y);
	printf("%#010x %s %#010x = %#010x\n", x, "|", y, x | y);
	printf("%#010x %s %#010x = %#010x\n", x, "^", y, x ^ y);
	printf("\n");


	// Calculate some masks with leading 0's, m 1's, and p 0's
	// (m+p < length of bitstring)
	//
	int m, p;
	m = 24;
	printf("Masks with %d 1 bits:\n", m);
	for (p = 0; p <= 32-m; p++) {
		printf("%#010x\n", ((1 << m) - 1) << p);
	}
}
