//Jamal Kharrat Section 1


// CS 350, Fall 2013
// Lab 2: Declaring, manipulating, and printing signed and unsigned integers of various lengths
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>	// to access printf, scanf
int main() {
	printf("CS 350 Lab 2 for %s\n\n", "Jamal Kharrat Section 1");
    
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
	printf("type unsigned char takes %ld byte(s)",sizeof(unsigned char));
    printf("has max value of %d = %#hhx\n", ch2,ch2);
    ch2++;
    printf("Adding 1 yields %d = %#hhx\n", ch2, ch2);
    printf("\n");
    
    short int shrtInt = 32767 ;
    printf("the type short int takes %ld byte(s)",sizeof(short int));
    printf("has the maximum value of %d = %#hx\n",shrtInt,shrtInt);
    shrtInt++;
    printf("Adding 1 yields %d = %#hx\n", shrtInt, shrtInt);
    printf("\n");
    
    unsigned short unsignedShort = 65535;
    printf("The type unsigned short takes %ld byte(s)",sizeof(unsigned short));
    printf("Has the maximum value of %d= %#hx\n",unsignedShort,unsignedShort);
    unsignedShort++;
    printf("Adding 1 yields %d = %#hx\n",unsignedShort,unsignedShort);
    printf("\n");
    
    int integer = 2147483647;
    printf("the type int takes %ld byte(s)",sizeof(int));
    printf("has the maximum value of %d = %#x\n",integer,integer);
    integer++;
    printf("Adding 1 yields %d = %#x \n",integer,integer);
    printf("\n");
    
    
    unsigned int unsignedInt= (unsigned int)0xffffffff;
    printf("the type unsigned int takes %ld byte(s)",sizeof(unsigned int));
    printf("has the maximum value of %u = %#x\n",unsignedInt,unsignedInt);
    unsignedInt++;
    printf("Adding 1 yields %d = %#x \n",unsignedInt,unsignedInt);
    printf("\n");
    
    
    
    long int longInt = (long int)0x7fffffffffffffff;
    printf("the type long takes %ld byte(s)",sizeof(long));
    printf("has the maximum value of %lu = %#lx\n",longInt,longInt);
    longInt++;
    printf("Adding 1 yields %lu = %#lx \n",longInt,longInt);
    printf("\n");
    
    
    unsigned long int unsignedLongInt = (unsigned long int)0xffffffffffffffff;
    printf("the type unsigned long takes %ld byte(s)",sizeof(unsigned long));
    printf("has the maximum value of %lu = %#lx\n",unsignedLongInt,unsignedLongInt);
    unsignedLongInt++;
    printf("Adding 1 yields %lu = %#lx \n",unsignedLongInt,unsignedLongInt);
    printf("\n");
    
    
	return 0;
}
