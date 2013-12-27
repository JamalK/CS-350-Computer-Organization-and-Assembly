

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
    printf("CS 350 Lab 1 for %s\n\n", "Daniela Martinez Section 02"); 
    
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
    
    short int ch3 = (short int) 0x7fff;
    printf("type short int takes %ld byte(s), ", sizeof(short int));
    printf("has max value of %d = %#hx\n", ch3, ch3);
    ch3++;
    printf("Adding 1 yields %d = %#hx\n", ch3, ch3);
    printf("\n");

    unsigned short int ch4 = (unsigned short int) 0xffff;
    printf("type unsigned short int takes %ld byte(s), ", sizeof(unsigned short int));
    printf("has max value of %u = %#hx\n", ch4, ch4);
    ch4++;
    printf("Adding 1 yields %u = %#hx\n", ch4, ch4);
    printf("\n");

    int ch5 = (int) 0x7fffffff;
    printf("type int takes %ld byte(s), ", sizeof(int));
    printf("has max value of %d = %#x\n", ch5, ch5);
    ch5++;
    printf("Adding 1 yields %d = %#x\n", ch5, ch5);
    printf("\n");

    unsigned int ch6 = (unsigned int) 0xffffffff;
    printf("type unsigned int takes %ld byte(s), ", sizeof(unsigned int));
    printf("has max value of %u = %#x\n", ch6, ch6);
    ch6++;
    printf("Adding 1 yields %u = %#x\n", ch6, ch6);
    printf("\n");

    long int ch7 = (long int) 0x7fffffffffffffff;
    printf("type long int takes %ld byte(s), ", sizeof(long int));
    printf("has max value of %ld = %#lx\n", ch7, ch7);
    ch7++;
    printf("Adding 1 yields %ld = %#lx\n", ch7, ch7);
    printf("\n");

    unsigned long int ch8 = (unsigned long int) 0xffffffffffffffff;
    printf("type unsigned long int takes %ld byte(s), ", sizeof(unsigned long int));
    printf("has max value of %lu = %#lx\n", ch8, ch8);
    ch8++;
    printf("Adding 1 yields %lu = %#lx\n", ch8, ch8);
    printf("\n");




    return 0;
}
