//
//  main.c
//  Lab 5
//
//  Created by Jamal Kharrat on 9/30/13.
//  Copyright (c) 2013 Jamal Kharrat. All rights reserved.
//

#include <stdio.h>

/* Interface Methods */
void shfting (int rightShift, int leftShift, unsigned int x);

int main()
{

    // Printing my name here
    printf("Jamal Kharrat CS 350 Section 1 Lab 5\n");


    //Defining Integers
    unsigned int input;
    int rightShift, leftShift;

    //do while loop that breaks when input = 0
    do {
        printf("Enter X in hex (0 to stop):\n"); //Prompting for x
        
        scanf("%x",&input); //scaning input
        
        if (input  == 0 ) {     //if input ==0 message
            printf("Quitting Application Goodbye.\n");
            return 1; //quiting the application
        }
        else
        {
            printf("Left and right endpoints //left space right//:  ");  //Prompting for left and right end point
            scanf("%d %d",&leftShift,&rightShift); //scaning left and right end point
            if (leftShift < 0 || (rightShift > 31 || rightShift <= 0)) {            //condition to check if left and right are valid
                printf("Illegal Argument\n Left End Point : %d\n Right End Point : %d\n",leftShift,rightShift);
                return 1;//quit the app
            }
            
                printf("Right end point : %d \n",rightShift); //printing left and right end points
                printf("Left End point : %d \n",leftShift);
                shfting(rightShift, leftShift, input); //calling the function shifting which does the shift
            }
  
        
    } while (input != 0); //do while end

    return 0;
}

void shfting (int rightShift, int leftShift, unsigned int x)
{
    
    //defining Mask
    unsigned int mask = 0xffffffff;
    
    //left shifting and anding to get the result
    mask = mask >> (leftShift);
    x=x & mask;
    x= x >> (31-rightShift);
    printf("X[%d:%d] =  0x%x = %d    ",leftShift,rightShift,x,x); //print the result to the console 

    
}
