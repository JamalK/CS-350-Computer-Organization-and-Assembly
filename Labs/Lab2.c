/* CS 350, Spring 2013
 * Lab 2 -- Converting an integer to a given base
 *
 * Illinois Institute of Technology, (c) 2013, James Sasaki
 */

/* This program repeatedly converts a value to a given base.
 * The value is converted to an equivalent array of digits
 * (each >= 0 and < base), and then we print the array.
 * We convert value & base pairs until the value is < 1 or base < 2.
 */
#include <stdio.h>
#include <strings.h>

#define ARRAYLEN 20

/* prototypes */
void break_up(int value, int base, int digits[], int len);
void print_digits(int digits[], int n);

int main() {
	printf("CS 350 Lab 2 for %s\n\n", "Andrey Danilkovich, CS 350-02");  // <-- Fill in
    
	int value, base;
	int digits[ARRAYLEN];
    int n = 0;  // set n to zero initially
    
    //set array to all zeros
    
    int i;
    for(i = 0; i < 20; i++)
    {
        digits[i] = 0;
    }
    
	/* Read an integer value to convert and the base to convert it to
	 */
	printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
	scanf("%d %d", &value, &base);
    
	/* Quit if the value is < 1 or the base is < 2.  Otherwise,
	 * call break_up to fill the digits array with values and
	 * then call print_digits to print out the array.  Then
	 * prompt, read another input, and repeat.
	 */
	while (value >= 1 && base >= 2) {
		
        
        break_up(value, base, digits, ARRAYLEN);
		print_digits(digits, n);
        
        // set array to all zeros
        
        
        
        for(i = 0; i < 20; i++)
        {
            digits[i] = 0;
        }
        
		printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
		scanf("%d %d", &value, &base);
        
        
	}
}

/* break_up takes a value, a base, an array of digits, and
 * the length of the array and converts the value into a
 * sequence that represents the value in the given base.
 * The sequence is stored in the digits array.
 * Formally, on return we should have
 *
 * passed value
 *   = digits[0] * base^(len-1)
 *     + ...
 *     + digits[i] * base^(len-i-1)
 *     + ...
 *     + digits[len-1] * base^0
 *
 * If the value is too large to be represented (we have a
 * value that would need a digits[-1] * base^len position),
 * then we complain and print out the unrepresentable part
 * of the value (namely, passed value / base^len).
 */
// *** STUB *** declare the break_up function

/* print_digits takes an array of integers and the length of
 * the array and prints out the integers on one line, separated
 * by a space.
 */

void break_up(int value, int base, int digits[ARRAYLEN], int len)
{
    int i;
    len = 0;
    
    for (i = 0; 0 < value; i++)
    {
        if(value >= 1048576)
        {
            printf("You have an overflow. Printing out the unrepresentable part.\n");
        }
        digits[i] = value % base;
        value = value/base;
        len ++;
    }
    /*
    if(value > 1048576)
    {
        printf("You have an overflow. Printing out the unrepresentable part.\n");
        for (i = 0; i < 20; i++)
        {
            digits[i] = 0;
            //digits[i] = value % base;
            //value = value/base^(len);
        }
        
    }
     */

}

void print_digits(int digits[ARRAYLEN], int n)
{
    //Reverse Print Loop
    
    int i;
    
    for (i = 19; i >= 0; i--)
    {
        printf("%d " , digits[i]);
    }
    printf("\n");
     
    //Simple Print In Order
    /*
    int i;
    
    for (i = 0; i < 20; i++)
    {
        printf("%d " , digits[i]);
    }
    printf("\n");
     */
    
    
}


