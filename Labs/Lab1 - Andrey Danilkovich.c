/*
 
 Solutions to Problems:
 Part C.
 
 1.
    (a). Sign Magnitute
    
    110111 = -(10111) = -23
    negative = 010111 = 23
 
    (b). 1's Compliment
 
    110111 = -8
    negative 001000 = 8
 
    (c). 2's Compliment
 
    110111 = -9
    001001 = 9
 2.
    (a). Sign Magnitute
    000000, 100000
 
    (b). 1's Compliment
    000000, 111111 
 
    (c). 2's Compliment
    000000
 
 3.
    (a). Sign Magnitute
    111111 = -31
 
    (b). 1's Compliment
    100000 = -31
 
    (c). 2's Compliment
    100000 = -32
 
 4.
    (a). Sign Magnitute
    No overflow
 
    (b). 1's Compliment
    No overflow
 
    (c). 2's Compliment
    Yes, taking the negative of the most negative number results in overflow
 
 5.
    (a). Sign Magnitute
      111011
     +101110
    =1101001, which is overlow if taken in the 6 bit perspective. But, the number equals the correct sum.
 
    (b). 2's Compliment
    111011 is the 2's compliment representation of 000101 = 5
 
    (c). 2's Compliment
    101110 is the twos compliment representation of 010010 = 18
 
    (d). 1101001 is the 2's compliment representation of 0010111 = 23
 
 6. 12+18 =  30
    001100 = 12
   +010010 = 18
 ------------------
   =011110 = 30
 
 7. 13-30=-17
    00110 + -(011110)
 
    001101 = 13
   +100010 = -30
 ------------------
   =101111 = -17
 
 8. -25-7=-32
 
    -(100111) = -25
    +(111001) = -7
 ------------------
    =100000 = -32
 
 
 9. 24+10=34
    011000 = 24
   +001010 = 10
 ------------------
   =100010 = 34, OVERFLOW! Answer is -34, which does not equal 34
 
 10. 428
     Binary = 110101100
     Octal  = 110 101 100 = 654
     Hex    = 0001 1010 1100 0001 1010 1100 = 1AC
 
 11. A63CB59
     1010 0110 0011 1100 1011 1001 - binary
     000101001100011110010111001000101001100011110010111001
     Octal = 1230745531
 
 12.
    (a). unsigned binary = 255
    (b). 2's compliment = 00000001 - FF = -1
    (c). 1's compliment = -0
 
 13.
    (a). 16's comp - 0AA9 + 1 = 0AAA
    (b). F556 = 1111 0101 0101 0110
    (c). 2's comp = 0000 1010 1010 1010
    (d). Hex of (c) = 0AAA
 
*/




// CS 350, Spring 2013
// Lab 1 -- Declaring, manipulating, and printing signed and unsigned integers of various lengths
// version of 2013-02-01
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

/* *** NOTE ***
 * Depending on your machine, you may need to print sizeof(...) using %d not %ld
 */

#include <stdio.h>  // to access printf, scanf

int main()
{
    printf("CS 350 Lab 1 for %s\n\n", "Andrey Danilkovich, CS 350-02 ");  // Name and Lab
    
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
    
    // Andrey's code starts here:
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
