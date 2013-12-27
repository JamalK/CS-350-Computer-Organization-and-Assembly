// ** Skeleton ** <-- remove this line and complete the program

// CS 350, Fall 2012
// Lab 1 -- Declaring, manipulating, and printing signed and unsigned integers of various lengths
// version of 2013-01-28, 11:26 am
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

/* *** NOTE ***
 * Depending on your machine, you may need to print sizeof(...) using %d not %ld
 */

#include <stdio.h>  // to access printf, scanf

int main() {
    printf("CS 350 Lab 1 for %s\n\n", "***Fill in your name and section ***");  // <-- Fill in your name and section and remove this comment
    
    // For each of the types char, unsigned char, short int, unsigned short int,
    // int, unsigned int, long int, and unsigned long int, we print out:
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
    printf("type unsigned char takes %ld byte(s), ", sizeof(unsigned char));
    printf("has max value of %u = %#hhx\n", ch2, ch2);
    ch2++;
    printf("Adding 1 yields %u = %#hhx\n", ch2, ch2);
    printf("\n");
    
    // *** STUB *** <-- replace this comment with your code
    
    return 0;
}