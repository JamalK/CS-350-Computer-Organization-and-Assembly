//Jamal E. Kharrat Section 1

// CS 350, Fall 2013
// Lab 1: Fix syntax & semantics errors
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

// Compile this file on alpha.cs.iit.edu with gcc -lm filename.c

#include <stdio.h>	// to access printf, scanf

int main() {
    
    
	printf("CS 350 Lab 1 for %s\n\n", "***Jamal Kharrat Section 1 ***");  
    
	int n = 5, a[5] = {1, 3, 5, 7, 9};	// Declare & initialize array of length 5
	int  sum=0;
    
    int i=0;
    
	for (i = 0; i < n; i++)
    {		// Sum up the 5 elements of the array
		sum = sum + a[i];
    }
    
   
        printf("Enter an integer x: ");	// Prompt the user
    
        int x;
    
        scanf("%d", &x);					// Read in the integer
        
        // Print out thexsxc sum, the division we're performing, and the result (without truncation)
        // E.g., The sum of the array is 25; 25/2 = 12.500000
        //declare a double variable to show the results of division without truncation.
    
        float division =(float)  sum/x;
    
        printf("The sum of the array is %d; %d/%d = %f\n", sum, sum,x,division);
        return 0;
    }

 
/*
 
 //C. Written Problems
 
 1-
 
 a)
 In Sign Magnitude 110111 has the decimal value of -23.
 The bit string for the negative of 110111 is 010111
 
 b)
 In 1's Complement 110111 has the decimal value of -8
 The bit string for the negative of 110111 is 010111
 
 c)
 In 2's Complement 110111 has the decimal value of -9
 The bit string for the negative of 110111 is 001001
 
 2-
 
 a)
 In Sign magnitude 000000 represents Zero.
 
 b)
 In 1's Complement 000000 or 111111 represents Zero.
 
 c)
 In 2's Complement 000000 represents Zero
 
 3-
 
 a)
 In Sign Magnitude, the most negative 6-bit String is 111111
 and has the decimal equivalent of -31.
 
 b)
 In 1's Complement, the most negative 6-bit String is 100000
 and has the decimal equivalent of -31.
 
 c)
 In 2's Complement, the most negative 6-bit String is 100000
 and has the decimal equivalent of -32
 
 4-
 
 a)Sign Magnitude does NOT cause overflow.
 b)1's Complement does NOT cause overflow.
 c)2's Complement does cause an overflow
 when we want to take the negative of the most negative number.
 
 5-
 001001.
 
 6-
 9
 
 7-
 111011 is the 2's complement representation of 59.
 the negative of it will be -5 000101.
 
 8-
 001110 is the 2's complement representation of 14.
 14
 Verification (14-5=9)
 
 9-
 12+18 = 001100 + 010010 = 011110 = 30
 
 10-
 13-30 = 001101 - 011110 = 001100 + (-011110) = 001101 + 100010 = 101111 = -(010001) = -17
 
 11-
 -25-7 = -(011001)-(000111) = 100111 + 111001 = -(100000)= 100000 = -32
 
 12-
 24+10 = 011000 + 001010 = 100010 = -30 (Incorrect answer. Overflow case)
*/
