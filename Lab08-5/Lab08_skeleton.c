
// Jamal Kharrat Section 1


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
    void dumpControlUnit(/*int pc, int ir, */ int regs[]);
    void dumpRegisters(int regs[]);
    void dumpMemory(int mem[]);
    void instruction_cycle(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.
//
#define NBR_REGS 10    // Number of CPU Registers
#define MEMLEN 100		//Number of  Memory addresses
    // *** WILL BE ADDED TO IN LAB 9 ***
    int running;          // true iff instruction cycle is active
	int regs[NBR_REGS];   // general-purpose registers
	int mem[MEMLEN];      // main memory
	



// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("CS 350 Lab 8, Jamal Kharrat\n");

	int pc=0;
	int ir=0;

	initCPU();
	readMemory();
	char input;
	int counter =0;
	char prompt[] = "> ";			//prompting sign
	printf("\nBeginning execution:\n");
	printf("At the %sprompt, press return to execute the next instruction\n", prompt);
	printf("(or d to dump registers and memory, q to quit, or h or ? for help)\n");

	char command[80];
	int commands_done = 0; // true iff simulator quit command seen

	printf("%s", prompt);
	fgets(command, sizeof command, stdin); 
	  // Read through end of current line.
	do
    {
        scanf("%c", &input);
        if(input == '\r' | input == '\n')
        {
            instruction_cycle(pc);
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
void helpMsg(void) {
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
// Initialize the running flag to true.
//
void initCPU(void) {
	printf("*** STUB *** initCPU\n");


	int i;
	for (i = 0; i < NBR_REGS; i++)
		regs[i] = 0;
	for (i = 0; i < MEMLEN; i++)
		mem[i] = 0;
}

// Read and dump initial values for memory
//
void readMemory(void) {
	int loc = 0;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");
	int i =0;
	int j;
	while(mem[i-1] < 9999 | mem[i-1] < -9999)
	{
		printf("Loc %.2d:", loc);
		scanf("%i", &mem[i]);
		loc++;
		i++;
	}
	// Clear the memory if the value doesn't match the above conditions
	for (j= 0 ; j < 99; j++)
	{
		if(mem[j] > 9999 & mem[j] > -9999)
        {
            mem[j] = 0;
        }
    }

	printf("*** STUB *** readmemory\n");

// *** You might need this after reading the sentinel ***
//	fgets(skip, sizeof skip, stdin);   // Clear the \n at end of terminating line

	printf("\nInitial value of memory:\n");
	dumpMemory(mem);
}


// dumpControlUnit(/*pc,ir,*/regs): Dump the control unit (pc, ir, and data registers).
// [For lab 8, just the registers]
// 
void dumpControlUnit(/*pc,ir,*/int regs[]) {
	// *** STUB ***
	printf("*** STUB *** dumpControlUnit\n");
	dumpRegisters(regs);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(int regs[]) {
	// *** STUB *** Hint: How do printf formats %d, %5d, %-5d, %05d, and % 05d differ?
	int i =0;


	printf("*** STUB *** dumpRegisters\n");
	for (i = 0; i < NBR_REGS; i++)
	{
		printf("R%d:  %04d  ",i,regs[i]);
		if (i==4)
		{
			printf("\n");
		}
	}


}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(int mem[]) {
	printf("*** STUB *** dumpMemory\n");
	int i=0;
	int j=0;

	// for (j = 0; j < 10; j++)
	// {
	// 	printf("%02d \n", j );
	// }

	for (i = 0; i < MEMLEN; i++)
	{
		
		if (i%10 == 0)
		{

			printf("\n%02d ",i);
		}
		printf("%04d    ",mem[i]);


	}
	printf("\n");

}


// Execute one instruction cycle.
//
int call_nbr = 0; // For Lab 8, we just print a message and halt after the 10th call
#define min(a, b) (((a) < (b)) ? (a) : (b))
void instruction_cycle(int mem[], int regs[], int PC) {

	// For Lab 8, we just print a message and halt after the 10th call
	//
	++call_nbr;
	char suffix[][4] = {"", "st","nd","rd","th"};
	printf("Calling instruction_cycle for %d%s time\n", call_nbr, suffix[min(call_nbr,4)]);
	if (call_nbr == 10) {
		printf("\nHalting\n");
		running = 0;
	}
	return;
}
