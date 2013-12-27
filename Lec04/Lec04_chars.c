// CS 350, Fall 2013
//
// chars.c: Print characters and their ASCII integers (in
// decimal and hex)
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>

int main() {
	printf("character %c = %d = %#x\n", '0', '0', '0');
	printf("character %c = %d = %#x\n", '1', '1', '1');
	printf("character %c = %d = %#x\n", '2', '2', '2');
	printf("...character %c = %d = %#x\n", '9', '9', '9');
	printf("\n");

	printf("character %c = %d = %#x\n", 48, 48, 48);
	printf("character %c = %d = %#x\n", 49, 49, 49);
	printf("...character %c = %d = %#x\n", 57, 57, 57);
	printf("\n");

	printf("character %c = %d = %#x\n", 'a', 'a', 'a');
	printf("character %c = %d = %#x\n", 'b', 'b', 'b');
	printf("...character %c = %d = %#x\n", 'z', 'z', 'z');
	printf("\n");

	printf("character %c = %d = %#x\n", 'A', 'A', 'A');
	printf("character %c = %d = %#x\n", 'B', 'B', 'B');
	printf("...character %c = %d = %#x\n", 'Z', 'Z', 'Z');
	printf("\n");

	printf("character %c = %d = %#x\n", '\n', '\n', '\n');
	printf("character %c = %d = %#x\n", 9, 9, 9);
	printf("character %c = %d = %#x\n", '\0', '\0', '\0');
}
