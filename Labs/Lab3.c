/* CS 350, Spring 2013
 * Lab 3 -- Converting an integer to a given base
 *
 * Illinois Institute of Technology, (c) 2013, James Sasaki
 */

/* Conversion to Decimal Program
 *
 * Convert the string representation of a 2's complement binary integer to its int
 * equivalent.
 *
 * Calculate the 2's complement negative of a binary integer represented by a string.
 *
 */

//
//  Created by Andrey Danilkovich on 2/13/13.
//  Copyright (c) 2013 Andrey Danilkovich. All rights reserved.
//

#include <stdio.h>
#include <strings.h>
#include <math.h>

#define ARRAYLEN 32

/* prototypes */
void convert(char binary[]);        // convert binary string to decimal and take 2's compliment negation
void printname();                   // print name and lab number

int main()
{
    char binary[ARRAYLEN];
    
    printname();                    // call print name function
    
    while (strcmp(binary, "q") != 0)
    {
        printf("Enter a bitstring (q for quit): ");
        
        scanf("%s", &binary);
        
        // Print quitting message
        
        if(strcmp(binary, "q") == 0)
        {
            printf("\n\nQuitting Program...\n\n");
            return 0;
        }
        
        convert(binary);
    }
    return 0;
}

void printname()
{
    printf("CS 350 Lab 2 for %s\n", "Andrey Danilkovich, CS 350-02");
    printf("* Conversion to Decimal Program *\n\n");
}

void convert(char binary[])
{
    int i, j;                                   // declare counter
    int sum = 0;                                // set sum to 0
    int newlength = (int)strlen(binary);        // get string length of binary input
    
    /* TESTS
     
    int newsize = sizeof(binary);
    printf("New size %d\n", newsize); */
    
    // positive for loop
    for (i = 0 ;i < newlength; i++)
    {
        if(binary[i] == '0' || binary[i] == '1')
        {
            int digit = binary[i] - '0';
            sum += (digit * (pow(2, newlength-i-1)));
        }
        else
        {
            printf("Invalid Entry: %c\n", binary[i]);
            printf("Please try again\n\n");
            
            break;
        }
    }
    
    // if first digit is negative - calculate the negative amount
    if (binary[0] == '1')
    {
        sum = sum - (pow(2, newlength));        // subtract negation and get new value
    }
   
    // print binary and decimal values
    printf("\n ** Binary string:  %s\n", binary);
    printf(" ** Decimal value:  %d\n", sum);
    
    // loop to get 2's compliment
    for (i = newlength; i >= 0; i--)
    {
        if(binary[i] == '1')
        {
            for (j = i - 1; j >= 0; j--)
            {
                if(binary[j] == '1')
                    binary[j] = '0';
                else if (binary[j] == '0')
                    binary[j] = '1';
            }
            break;
        }
    }
    
    printf(" ** 2's complement negative:  %s\n\n", binary); // print 2s compliment

}

