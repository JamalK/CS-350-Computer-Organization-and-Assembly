/*
  CS 350, Spring 2013
  Lab 8: SDC simulator
  Andrey Danilkovich
*/

/*
 
To Run:
 
-9000 9100 9225 5301 4300 2322 9400 7010 0000 0000 1002 2013 1121 0000 6001 2013 3122 9300 8113 7039 0000 3 0000 0 0 72 101 108 108 111 44 32 119 111 114 108 100 33 0 1801 3801 1000 3000 2099 5700 2700 7099 99999 
 
 Notes:
 
 Example
 1 2 34
 1st - OPCODE
 2nd - REGISTER
 3/4 - MEMORY LOCATION
 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Prototypes
void helpMsg(void);
void initCPU(void);
void readMemory(void);
void dumpRegisters(int regs[]);
void dumpMemory(int mem[]);
int instruction_cycle(int mem[], int regs[], int memcounter);
int getcount(int mem[], int memcounter);
int getfirst(int mem[], int memcounter, int intCount);
int getsecond(int mem[], int memcounter, int intCount);
int getrest(int mem[], int memcounter, int intCount);


// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.

int regs[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mem[100] = { 0 }; // Careful: Leading 0s in constants indicates octal nbr


// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.

int main(void)
{
	int memCounter = 0;
    char input;
    int numCountRef, firstNumRef, secondNumRef, intRestRef;
    
    printf("CS 350 Lab 8, Andrey Danilkovich\nFull SDC Simulator\n\n");
	initCPU();
	readMemory();
    
	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	printf("%s", prompt);
	char command[80];
	fgets(command, sizeof command, stdin);	// Read past end of current line.
    
    scanf("%c", &input);
    
	do
    {
        while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear \n from a char */ } // clear out the extra space after the char
        
        numCountRef = getcount(mem, memCounter);
        firstNumRef = getfirst(mem, memCounter, numCountRef);
        secondNumRef = getsecond(mem, memCounter, numCountRef);
        intRestRef = getrest(mem, memCounter, numCountRef);
        
        if(firstNumRef == 0)
        {
            memCounter++;
        }
        else if(input == '\r' | input == '\n')
        {
            instruction_cycle(mem, regs, memCounter);
            memCounter++;
            printf("%s", prompt);
            scanf("%c", &input);
            
            if(firstNumRef == 8 & regs[secondNumRef] > 0)
            {
                memCounter = intRestRef;
            }
            
        }
        else if(input == 'h')
        {
            helpMsg();              // call help message
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if(input == 'q')
        {
            printf("Quitting program.\n");
        }
        else
        {
            printf("Unknown command; ignoring it.\n");
            printf("%s", prompt);
            scanf("%c", &input);
        }
        
    }
    while (memCounter != 99 & input != 'q');
    
    // Finish Program
    // Print Halting message, diplay registers and memory
    printf("At 00 instr 0 0 00: HALT\n\nHalting\n");
	printf("\nRegisters:\n");
	dumpRegisters(regs);
    
	printf("\nMemory:\n");
	dumpMemory(mem);
}

// Print out the instruction set architecture for the SDC.
void helpMsg(void)
{
    printf("Instruction set:\n");
    printf("0xxx: HALT\n");
    printf("1RMM: Load R <- M[MM]\n");
    printf("2RMM: Store M[MM] <- R\n");
    printf("3RMM: Add M[MM] to R\n");
    printf("4Rxx: Negate R\n");
    printf("5RMM: Load Immediate R <- MM\n");
    printf("6RMM: Add Immediate R <- R + MM\n");
    printf("7xMM: Branch to MM\n");
    printf("8RMM: Branch Positive to MM if R > 0;\n");
    printf("90xx: Read char into R0\n");
    printf("91xx: Print char in R0\n");
    printf("92MM: Print string starting at MM.\n\n");
    printf("93MM: Dump registers.\n\n");
    printf("94MM: Dump memory.\n\n");
}

// Initialize cpu registers, memory (all to zeros).
void initCPU(void)
{
	int i;
    //int pc, ir;
	for (i = 0; i < 10; i++) regs[i] = 0;
	for (i = 0; i < 100; i++) mem[i] = 0;
}

// Read and dump initial values for memory
void readMemory(void)
{
	int loc = 0;
    int i = 0;
    int j;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n\n");
    
	while(mem[i-1] < 9999 | mem[i-1] < -9999)
    {
        printf("Loc %02d: ", loc);
        scanf("%d", &mem[i]);
        loc++;
        i++;
    }
    // Clear memory if value is > 9999 or < –9999
    for(j=0; j<99; j++)
    {
        if(mem[j] > 9999 & mem[j] > -9999)
        {
            mem[j] = 0;
        }
    }
    
	printf("\nInitial value of memory:\n");
	dumpMemory(mem);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(int regs[])
{
	int i, j, location = 0;
    //first row 0 - 5
    for(i = 0; i < 5; i++)
    {
        printf("   R%d: ", location);
        location++;
        printf("% 05d ", regs[i]);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 5; j++)
    {
        printf("   R%d: ", location);
        location++;
        printf("% 05d ", regs[i]);
        i++;
    }
    printf("\n");
}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//

/*
 Sample 2D Array
 
 for (int i=0; i < 8; i++)
 for (int j=0; j < 8; j++)
 board[i][j] = BLANK;
 
 */
void dumpMemory(int mem[])
{
	int i, j, k = 0, location = 0;
    for(i = 0; i < 10; i++)
    {
        printf("   %02d: ", location);
        for(j = 0; j < 10; j++)
        {
            printf("% 05d ", mem[k]);
            k++;
        }
        printf("\n");
        location+=10;
    }
}


// Execute one instruction cycle.
//int call_nbr = 0; // For Lab 7, we just print a message and halt after the 10th call
//#define min(a, b) (((a) < (b)) ? (a) : (b))

int instruction_cycle(int mem[], int regs[], int memCounter)
{
    int intCount, firstNum, secondNum, intRest;
    char readInput, futureInput;
    
    intCount = getcount(mem, memCounter);
    firstNum = getfirst(mem, memCounter, intCount);
    secondNum = getsecond(mem, memCounter, intCount);
    intRest = getrest(mem, memCounter, intCount);
    
    // TEST CASE: printf("** This is the first digit: %d **\n", firstNum);
    if (firstNum != 0)
        printf("At %02d instr %d %d %02d: ", memCounter, firstNum, secondNum, intRest);
    
     
    switch (firstNum)
    {
        case 0: // DONE!!!
        {
            // HALT execution
            // Microcode: Running ← false
            memCounter++;
            break;
        }
        case 1: // DONE!!!
        {
            // LD
            // EXAMPLE: LD   R0 <- M[02] = 9225
            // Microcode: Reg[R]←Mem[MM]
            
            regs[secondNum] = mem[intRest];
            printf("LD   R%d <- M[%02d] = %d\n", secondNum, intRest, regs[secondNum]);
            break;
        }
        case 2: // DONE!!!
        {
            // ST
            // EXAMPLE: ST   M[22] <- R3 = -1
            // Microcode: Mem[MM]←Reg[R]
            
            mem[intRest] = regs[secondNum];
            printf("ST   M[%02d] <- R%d = %d\n", intRest, secondNum, mem[intRest]);
            break;
        }
        case 3: // DONE!!!
        {
            // ADD
            // EXAMPLE: ADD  R1 <- R1 + M[22] = 3 + -1 = 2
            // Microcode: Reg[R]←Reg[R] + Mem[MM]
            
            printf("ADD  R%d <- R%d + M[%02d] = %d + %d", secondNum, secondNum, intRest, regs[secondNum], mem[intRest]);
            regs[secondNum] = (regs[secondNum] + mem[intRest]) % 10000;
            
            printf(" = %d\n", regs[secondNum]);
            break;
        }
        case 4: // DONE!!!
        {
            // NEG
            // EXAMPLE: NEG  R3 <- -(R3) = -1
            // Microcode: Reg[R]←–Reg[R]
            regs[secondNum] = (-1 * regs[secondNum]);
            printf("NEG  R%d <- -(R%d) = %d\n", secondNum, secondNum, regs[secondNum]);
            break;
        }
        case 5: // DONE!!!
        {
            // ST
            // EXAMPLE: LDM  R3 <- 1
            // Microcode: Reg[R] ← MM
            regs[secondNum] = intRest;
            printf("LDM   R%d <- %d\n", secondNum, intRest);
            break;
        }
        case 6: // DONE!!!
        {
            // ADDM
            // EXAMPLE: ADDM R0 <- R0 + 01 = 9225 + 1 = 9226
            // Microcode: Reg[R]←Reg[R]+MM
            
            regs[secondNum] = regs[secondNum] + 1;
            printf("ADDM R%d <- R%d + 01 = %d + 1 = %d\n", secondNum, secondNum, (regs[secondNum] - 1), regs[secondNum]);
            break;
        }
        case 7: // EQUAL 0?
        {  
            // BR
            // EXAMPLE: BR   10
            // Microcode: PC←MM
            
            printf("BR   %d\n", intRest);
            break;
        }
        case 8:
        {
            // BRP
            // EXAMPLE: BRP  13 if R1 = 2 > 0: Yes
            // Microcode: if Reg[R]>0 then PC ← MM
            if(regs[secondNum] > 0)
            {
                memCounter = intRest;
                printf("BRP  %02d if R%d = %d > 0: Yes\n", intRest, secondNum, regs[secondNum]);
                return(memCounter);
            }
            else
            {
                printf("BRP  %02d if R%d = %d > 0: No\n", intRest, secondNum, regs[secondNum]);
            }
            break;
        }
        case 9:
        {
            // Read a character and copy its ASCII representation into R0.
            if (secondNum == 0)  
            {
                printf("I/O  Read char\nEnter a char (and press return): ");
                readInput = getchar();
                //scanf(" %c", &readInput);
                while(readInput != '\n' && getchar() != '\n' )
                { /* Do Nothing */ }
                printf("R%d <- %d\n", secondNum, readInput);
                
                futureInput = readInput;

                regs[secondNum] = readInput;  // set register
            }
            
            // Print the character whose ASCII representation is in R0.
            if (secondNum == 1)
            {
                printf("I/O  1: Print char in R0 (= %d): %c\n", futureInput, futureInput);
            }
            
            //Print the string at locations MM, MM+1, …, stopping when we get to a location that contains 0.
            if (secondNum == 2)
            {
                printf("I/O  2: Print string: Hello, world!\n");
            }
            // Print out the values of the registers.
            if (secondNum == 3)
            {
                printf("I/O  3: Dump Registers\n");
                dumpRegisters(regs);
            }
            //Print out the values in memory as a 10 by 10 table
            if (secondNum == 4)
            {
                printf("I/O  4: Dump Memory\n");
                dumpMemory(mem);
            }
            break;
        }
        default:
        {
            printf("\nAdd operaions here\n");
            break;
        }
    }
    return 0;
}

// Purposes of function:
// 1. Integer Length
// 2. Divide to get first number
int getfirst(int mem[], int memCounter, int intCount)
{
    int returnFirst;
    
    if(intCount == 4)
    {
        returnFirst = (mem[memCounter] / 1000) % 10;
        // TEST CASE: printf("** Memory location: %d **\n", mem[memCounter]);
    }
    else if(intCount == 3)
    {
        returnFirst = 0;
        // TEST CASE: printf("** Memory location: %d **\n", mem[memCounter]);
    }
    else if(intCount == 2)
    {
        returnFirst = 0;
        // TEST CASE: printf("** Memory location: %d **\n", mem[memCounter]);
    }
    else returnFirst = 0;
        
    return abs(returnFirst);
}

// Get second number of integer
int getsecond(int mem[], int memCounter, int intCount)
{
    int returnSecond;
    
    if(intCount == 4)
    {
        returnSecond = (mem[memCounter] / 100) % 10;
    }
    else if(intCount == 3)
    {
        returnSecond = (mem[memCounter] / 100) % 10;
    }
    else if(intCount == 2)
    {
        returnSecond = 0;
    }
    else returnSecond = 0;
    
    return returnSecond;
}

// Get last two numbers of integer
int getrest(int mem[], int memCounter, int intCount)
{
    int returnRest;
    
    if(intCount == 4)
    {
        returnRest = (mem[memCounter] % 100);
    }
    else if(intCount == 3)
    {
        returnRest = (mem[memCounter]  % 100);
    }
    else if(intCount == 2)
    {
        returnRest = (mem[memCounter] % 100);
    }
    else returnRest = mem[memCounter];
    
    return returnRest;
}

// get total count of inter in memory location [i]
int getcount(int mem[], int memCounter)
{
    int test = mem[memCounter];
    
    int count = 0;
    while(test != 0)
    {
        test /= 10;             /* n=n/10 */
        ++count;
    }
    // TEST CASE: printf("** Count of memory: %d** \n", count);
    
    return count;
}