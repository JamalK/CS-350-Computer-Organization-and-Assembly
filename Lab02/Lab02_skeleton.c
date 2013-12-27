// ** Skeleton ** <-- remove this line and complete the program
// *** Your name and section (replace this with the correct information ***
// (Also rename this file to Lab02_YourName_Section.c and remove this comment line)

// CS 350, Fall 2013
// Lab 2: Declaring, manipulating, and printing signed and unsigned integers of various lengths
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>	// to access printf, scanf

int main() {
	printf("CS 350 Lab 2 for %s\n\n", "***Fill in your name and section ***");  // <-- Fill in your name and section and remove this comment

	// For each of the types char, unsigned char, short int, unsigned short int,
	// and int, we print out:
	//     (1) The number of bytes it takes to store values of that type
	//     (2) The largest value of that type in decimal and in hex
	//     (3) The result of adding 1 to that largest value.
	//
	// [Note: Adding 1 to the largest value of a signed type should yield the
	// most negative value of that type; adding 1 to the largest value of an
	// unsigned type should yield 0.]

    char ch1 = (char) 0x7f;
    printf("type char takes %ld byte(s), ", sizeof(char));
    printf("has max value of %d = %#hhx\n", ch1, ch1);
    ch1++;
    printf("Adding 1 yields %d = %#hhx\n", ch1, ch1);
    printf("\n");

    unsigned char ch2 = (unsigned char) 0xff;
	// *** STUB *** <-- replace this comment with your code

	return 0;
}
