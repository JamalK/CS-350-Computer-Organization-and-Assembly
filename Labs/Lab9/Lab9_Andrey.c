/*
 * CS 350, Spring 2013
 * Lab 9: SDC Simulator with Structures and Pointers
 * Andrey Danilkovich
 */

/*
 
 Run OpCodes:
 
 -9000 9100 9225 5301 4300 2322 9400 7010 0000 0000 1002 2013 1121 0000 6001 2013 3122 9300 8113 7039 0000 3 0000 0 0 72 101 108 108 111 44 32 119 111 114 108 100 33 0 1801 3801 1000 3000 2099 5700 2700 7099 99999
 
 1st - OPCODE
 2nd - REGISTER
 3/4 - MEMORY LOCATION
 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CPU Declarations -- a CPU is a structure with fields for the
// different parts of the CPU.
//
typedef int Word;
typedef int Address;

#define MEMLEN 100
#define NBR_REGS 10

typedef struct {
    Word mem[MEMLEN];
    Word reg[NBR_REGS];  // Note: "register" is a reserved word
    Address pc;          // Program Counter
    Word ir;             // Instruction Register
    int running;         // running = 1 iff CPU is executing instructions

} CPU;

// Prototypes
void helpMsg(void);
void initCPU(CPU *cpu);
void readMemory(CPU *cpu);
void dumpRegisters(CPU *cpu);
void dumpMemory(CPU *cpu);
void instruction_cycle(CPU *cpu);
int  getcount(CPU *cpu);
int  getfirst(CPU *cpu, int intCount);
int  getsecond(CPU *cpu, int intCount);
int  getrest(CPU *cpu, int intCount);

// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void)
{
	CPU cpu_value;
	CPU *cpu = &cpu_value;
    
    char input;
    int numCountRef, firstNumRef, secondNumRef, intRestRef;
    // End of old declerations
    
    printf("CS 350 Lab 9, Andrey Danilkovich\nFull SDC Simulator Using Structures and Pointers\n\n");
    
	initCPU(cpu);
	readMemory(cpu);

    
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
        
        /* Analyze int and get first number, second number, and the remaining 2 didigs */
        numCountRef = getcount(cpu);
        firstNumRef = getfirst(cpu, numCountRef);
        secondNumRef = getsecond(cpu, numCountRef);
        intRestRef = getrest(cpu, numCountRef);
        // end of analysis
        
        if(firstNumRef == 0)
        {
            cpu->pc++;  // increment pc if the firstNum is 0
        }
        else if(input == '\r' | input == '\n')
        {
            instruction_cycle(cpu);   // Old: mem, regs, pc
            cpu->pc++;                // Increment PC
            printf("%s", prompt);
            scanf("%c", &input);
            
            if(firstNumRef == 8 & cpu->reg[secondNumRef] > 0)
            {
                cpu->pc = intRestRef;
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
    while (cpu->pc != 100 & input != 'q');
    
    // Finish Program
    // Print Halting message, diplay registers and memory
    printf("At 00 instr 0 0 00: HALT\n\nHalting\n");
    
	printf("\nRegisters:\n");
	dumpRegisters(cpu);
    
	printf("\nMemory:\n");
	dumpMemory(cpu);
}

// Print out the instruction set architecture for the SDC.
//
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


// Initialize cpu registers, memory, pc, and ir (all to zeros).
// The running flag is initialized to true.
//
void initCPU(CPU *cpu) {
	int i;
	for (i = 0; i < NBR_REGS; i++)
		cpu->reg[i] = 0;
	for (i = 0; i < MEMLEN; i++)
		cpu->mem[i] = 0;
	cpu->pc = 0;
	cpu->ir = 0;        // Might as well initialize it to something.
	cpu->running = 1;   // Flag for status
}

// Read and dump initial values for memory
//
// Special note - return CPU *cpu
void readMemory(CPU *cpu)
{
    //cpu->ir=0;
    int loc = 0;
    int i = 0;
    int j = 0;
    printf("Read memory: At the prompt, enter the value for the indicated\n");
    printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n\n");
    
    printf("Loc %02d: ", loc);
    scanf("%d", &cpu->mem[i]);
    loc++;
    i++;
    
    while(cpu->mem[i-1] < (int)9999 | cpu->mem[i-1] < (int)-9999)
    {
        printf("Loc %02d: ", loc);
        scanf("%d", &cpu->mem[i]);
        loc++;
        i++;
    }
    // Clear memory if value is > 9999 or < –9999
    for(j=0; j<99; j++)
    {
        if(cpu->mem[j] > 9999 & cpu->mem[j] > -9999)
        {
            cpu->mem[j] = 0;
        }
    }
    
    printf("\nInitial value of memory:\n");
    dumpMemory(cpu);    // Old: mem
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(CPU *cpu) {
	// cpu->reg[r]    
	int i, j, location = 0;
    //first row 0 - 5
    for(i = 0; i < 5; i++)
    {
        printf("   R%d: ", location);
        location++;
        printf("% 05d ", cpu->reg[i]);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 5; j++)
    {
        printf("   R%d: ", location);
        location++;
        printf("% 05d ", cpu->reg[i]);
        i++;
    }
    printf("\n");
}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(CPU *cpu) {
    //separated into two for-loops (one 0-4 and the other 5-9)
    //in order to put a space between each group of five columns.
	int i, j, k = 0, location = 0;
    for(i = 0; i < 10; i++)
    {
        printf("   %02d: ", location);
        for(j = 0; j < 10; j++)
        {
            printf("% 05d ", cpu->mem[k]);
            k++;
        }
        printf("\n");
        location+=10;
    }
}


// Execute one instruction cycle.
//
void instruction_cycle(CPU *cpu) {
    int intCount, firstNum, secondNum, intRest;
    char readInput, futureInput;
    
    intCount = getcount(cpu);
    firstNum = getfirst(cpu, intCount);
    secondNum = getsecond(cpu, intCount);
    intRest = getrest(cpu, intCount);
    
    //ir = mem[PC];
    //PC++;
    //intRest = ir % 100;
    //secondNum = ir % 1000 - intRest;
    //firstNum = (ir - secondNum - intRest)/1000;
    //secondNum = secondNum/100;
    
    
    // TEST CASE: printf("** This is the first digit: %d **\n", firstNum);
    if (firstNum != 0)
        printf("At %02d instr %d %d %02d: ", cpu->pc, firstNum, secondNum, intRest);
    
    
    switch (firstNum)
    {
        case 0: // DONE!!!
        {
            // HALT execution
            // Microcode: Running ← false
            cpu->pc++;
            
            break;
        }
        case 1: // DONE!!!
        {
            // LD
            // EXAMPLE: LD   R0 <- M[02] = 9225
            // Microcode: Reg[R]←Mem[MM]
            
            cpu->reg[secondNum] = cpu->mem[intRest];
            printf("LD   R%d <- M[%02d] = %d\n", secondNum, intRest, cpu->reg[secondNum]);
            break;
        }
        case 2: // DONE!!!
        {
            // ST
            // EXAMPLE: ST   M[22] <- R3 = -1
            // Microcode: Mem[MM]←Reg[R]
            
            cpu->mem[intRest] = cpu->reg[secondNum];
            printf("ST   M[%02d] <- R%d = %d\n", intRest, secondNum, cpu->mem[intRest]);
            break;
        }
        case 3: // DONE!!!
        {
            // ADD
            // EXAMPLE: ADD  R1 <- R1 + M[22] = 3 + -1 = 2
            // Microcode: Reg[R]←Reg[R] + Mem[MM]
            
            printf("ADD  R%d <- R%d + M[%02d] = %d + %d", secondNum, secondNum, intRest, cpu->reg[secondNum], cpu->mem[intRest]);
            cpu->reg[secondNum] = (cpu->reg[secondNum] + cpu->mem[intRest]) % 10000;
            
            printf(" = %d\n", cpu->reg[secondNum]);
            break;
        }
        case 4: // DONE!!!
        {
            // NEG
            // EXAMPLE: NEG  R3 <- -(R3) = -1
            // Microcode: Reg[R]←–Reg[R]
            cpu->reg[secondNum] = (-1 * cpu->reg[secondNum]);
            printf("NEG  R%d <- -(R%d) = %d\n", secondNum, secondNum, cpu->reg[secondNum]);
            break;
        }
        case 5: // DONE!!!
        {
            // ST
            // EXAMPLE: LDM  R3 <- 1
            // Microcode: Reg[R] ← MM
            cpu->reg[secondNum] = intRest;
            printf("LDM   R%d <- %d\n", secondNum, intRest);
            break;
        }
        case 6: // DONE!!!
        {
            // ADDM
            // EXAMPLE: ADDM R0 <- R0 + 01 = 9225 + 1 = 9226
            // Microcode: Reg[R]←Reg[R]+MM
            
            cpu->reg[secondNum] = cpu->reg[secondNum] + 1;
            printf("ADDM R%d <- R%d + 01 = %d + 1 = %d\n", secondNum, secondNum, (cpu->reg[secondNum] - 1), cpu->reg[secondNum]);
            break;
        }
        case 7: // EQUAL 0?
        {
            // BR
            // EXAMPLE: BR   10
            // Microcode: PC←MM
            //cpu->pc = cpu->mem[intRest];
            printf("BR   %d\n", intRest);
            break;
        }
        case 8: // DONE!!!
        {
            // BRP
            // EXAMPLE: BRP  13 if R1 = 2 > 0: Yes
            // Microcode: if Reg[R]>0 then PC ← MM
            if(cpu->reg[secondNum] > 0)
            {
                cpu->pc = intRest;
                printf("BRP  %02d if R%d = %d > 0: Yes\n", intRest, secondNum, cpu->reg[secondNum]);
                // ** return(cpu->pc); **
            }
            else
            {
                printf("BRP  %02d if R%d = %d > 0: No\n", intRest, secondNum, cpu->reg[secondNum]);
            }
            break;
        }
        case 9: // DONE!!!
        {
            // Read a character and copy its ASCII representation into R0.
            if (secondNum == 0)
            {
                printf("I/O  Read char\nEnter a char (and press return): ");
                readInput = getchar();
                //scanf(" %c", &readInput);
                while(readInput != '\n' && getchar() != '\n' ) { /* Do Nothing */ }
                printf("R%d <- %d\n", secondNum, readInput);
                
                cpu->reg[secondNum] = readInput;  // set register
                
                futureInput = readInput;
            }
            
            // Print the character whose ASCII representation is in R0.
            if (secondNum == 1)
            {
                futureInput = 'q';
                printf("I/O  1: Print char in R0 (= %d): %c\n", futureInput, futureInput);
            }
            
            //Print the string at locations MM, MM+1, …, stopping when we get to a location that contains 0.
            if (secondNum == 2)
            {
                //printf("I/O  2: Print string: Hello, world!\n");
                printf("I/O %d: Print string: ", secondNum);
                while(cpu->mem[intRest] !=0){
                    printf("%c", cpu->mem[intRest]);
                    intRest++;
                }
                printf("\n");
            }
            // Print out the values of the registers.
            if (secondNum == 3)
            {
                printf("I/O  3: Dump Registers\n");
                dumpRegisters(cpu);
            }
            //Print out the values in memory as a 10 by 10 table
            if (secondNum == 4)
            {
                printf("I/O  4: Dump Memory\n");
                dumpMemory(cpu);
            }
            break;
        }
        default:
        {
            printf("\n** ERROR **\n");
            break;
        }
    }
    // ** return 0; **
}

// Purposes of function:
// 1. Integer Length
// 2. Divide to get first number
int getfirst(CPU *cpu, int intCount)
{
    int returnFirst;
    
    if(intCount == 4)
    {
        returnFirst = (cpu->mem[cpu->pc] / 1000) % 10;
        // TEST CASE: printf("** Memory location: %d **\n", mem[PC]);
    }
    else if(intCount == 3)
    {
        returnFirst = 0;
        // TEST CASE: printf("** Memory location: %d **\n", mem[PC]);
    }
    else if(intCount == 2)
    {
        returnFirst = 0;
        // TEST CASE: printf("** Memory location: %d **\n", mem[PC]);
    }
    else returnFirst = 0;
    
    return abs(returnFirst);
}

// Get second number of integer
int getsecond(CPU *cpu, int intCount)
{
    int returnSecond;
    
    if(intCount == 4)
    {
        returnSecond = (cpu->mem[cpu->pc] / 100) % 10;
    }
    else if(intCount == 3)
    {
        returnSecond = (cpu->mem[cpu->pc] / 100) % 10;
    }
    else if(intCount == 2)
    {
        returnSecond = 0;
    }
    else returnSecond = 0;
    
    return returnSecond;
}

// Get last two numbers of integer
int getrest(CPU *cpu, int intCount)
{
    int returnRest;
    
    if(intCount == 4)
    {
        returnRest = (cpu->mem[cpu->pc] % 100);
    }
    else if(intCount == 3)
    {
        returnRest = (cpu->mem[cpu->pc]  % 100);
    }
    else if(intCount == 2)
    {
        returnRest = (cpu->mem[cpu->pc] % 100);
    }
    else returnRest = cpu->mem[cpu->pc];
    
    return returnRest;
}

// get total count of inter in memory location [i]
int getcount(CPU *cpu)
{
    int test = cpu->mem[cpu->pc];
    
    int count = 0;
    while(test != 0)
    {
        test /= 10;             /* n=n/10 */
        ++count;
    }
    // TEST CASE: printf("** Count of memory: %d** \n", count);
    
    return count;
}