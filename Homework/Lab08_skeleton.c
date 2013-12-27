// ** Skeleton ** <-- remove this line and complete the program
// *** Your name and section (replace this with the correct information ***
// (Also rename this file to Lab08_YourName_Section.c and remove this comment line)

// CS 350, Fall 2013
// Lab 8: SDC simulator framework
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>
#include <string.h>

// Prototypes
void helpMsg(void);
void initCPU(void);
void readMemory(void);
void dumpRegisters(int regs[]);
void dumpMemory(int mem[]);
int instruction_cycle(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.

int regs[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mem[100] = { 0 }; // Careful: Leading 0s in constants indicates octal nbr

// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.

int main(void)
{
	char input;
    int counter = 0;
    
    printf("CS 350 Lab 8, Jamal Kharrat\nSDC Simulator Framework\n\n");
	initCPU();
	readMemory();
    
	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	printf("%s", prompt);
	char command[80];
	fgets(command, sizeof command, stdin);	// Read past end of current line.
    
	do
    {
        scanf("%c", &input);
        if(input == '\r' | input == '\n')
        {
            instruction_cycle();
            printf("%s", prompt);
            counter++;
        }
        else if(input == 'q')
            printf("Quitting\n");   // display quiting message
        
        else if(input == 'h')      
            helpMsg();              // call help message
        
        else
        {
            printf("Invalid Input, try again: ");
            break;
        }
    }
    while (input != 'q' & counter < 10);
    
    
	printf("\nRegisters:\n");
	dumpRegisters(regs);
    
	printf("\nMemory:\n");
	dumpMemory(mem);
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void)
{
	printf("Lab 7 help message is a placeholder\n");
}

// Initialize cpu registers, memory (all to zeros).
//
void initCPU(void)
{
	int i;
	for (i = 0; i < 10; i++) regs[i] = 0;
	for (i = 0; i < 100; i++) mem[i] = 0;
}

// Read and dump initial values for memory
//
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
	// *** STUB *** Hint: How do printf formats %d, %5d, %-5d, %05d, and % 05d differ?
	int i, j, location = 0;
    //first row 0 - 5
    for(i = 0; i < 5; i++)
    {
        printf("   R%d: ", location);
        location++;
        printf("%04d ", regs[i]);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 5; j++)
    {
        printf("   R%d: ", location);
        location++;
        printf("%04d ", regs[i]);
    }
    printf("\n");
}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//


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
//
int call_nbr = 0; // For Lab 7, we just print a message and halt after the 10th call
#define min(a, b) (((a) < (b)) ? (a) : (b))
int instruction_cycle(void) {
	int halted = 0;
    
	// For Lab 7, we just print a message and halt after the 10th call
	//
	++call_nbr;
	char suffix[][4] = {"", "st","nd","rd","th"};
	printf("Calling instruction_cycle for %d%s time\n", call_nbr, suffix[min(call_nbr,4)]);
	if (call_nbr == 10) {
		printf("\nHalting\n");
		halted = 1;
		return 1;
	}
	return 0;
}