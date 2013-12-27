/*
 * CS 350, Spring 2013
 * Lab 9: SDC Simulator with Structures and Pointers
 */
#include <stdio.h>
#include <string.h>

// CPU Declarations -- a CPU is a structure with fields for the
// different parts of the CPU.
//
typedef int Word;
typedef int Address;

#define MEMLEN 100
#define NBR_REGS 10
#define arraylen 4

typedef struct {
	Word mem[MEMLEN];
	Word reg[NBR_REGS];  // Note: "register" is a reserved word
	Address pc;          // Program Counter
	Word ir[arraylen];   // Instruction Register
	int running;         // running = 1 iff CPU is executing instructions
} CPU;

// Prototypes
void helpMsg(void);
void initCPU(CPU *cpu);
void readMemory(CPU *cpu);
void dumpRegisters(CPU *cpu);
void dumpMemory(CPU *cpu);
void instruction_cycle(CPU *cpu);

// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("CS 350 Lab 9, Daniela Martinez\n");
	CPU cpu_value;
	CPU *cpu = &cpu_value;
	initCPU(cpu);
	readMemory(cpu);

	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	printf("%s", prompt);
	char command[80];
	fgets(command, sizeof command, stdin);	// Read past end of current line.

	char input;
	scanf("%c", &input);

	//loop
	while(input != 'q' && cpu->running != 0){
		if(input  == '\n'){
			instruction_cycle(cpu);
			//when the program reaches a Halt(running = false), it will break out of the loop and end the program
			if(cpu->running == 0)
				break;
			printf("%s", prompt);
		}

		else if(input == 'h'|| input == '?'){
			helpMsg();
			printf("%s", prompt);
			scanf("%c", &input);
		}
		scanf("%c", &input);
	}

	if(input == 'q')
		printf("Quitting\n");


	printf("\nRegisters:\n");
	dumpRegisters(cpu);

	printf("\nMemory:\n");
	dumpMemory(cpu);
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
	printf("Instruction Set:\n"
			" 0xxx: HALT\n"
			" 1RMM: Load Reg[R] <- Mem[MM]\n"
			" 2RMM: Store Mem[MM] <- Reg[R]\n"
			" 3RMM: Add M[MM] to Reg[R]\n"
			" 4Rxx: Negate Reg[R]\n"
			" 5RMM: Load immediate  Reg[R] <- MM\n"
			" 6RMM: Add immediate  Reg[R] <- Reg[R] + MM\n"
			" 7xMM: Branch to MM\n"
			" 8RMM: Branch positive to Mem[MM] if Reg[R] >0\n"
			" 90xx: Read character and copy to Reg[0]\n"
			" 91xx: Print character in Reg[0]\n"
			" 92MM: Print string starting at Mem[MM]\n"
			" 93MM: Dump Registers.\n"
			" 94MM: Dump Memory.\n");

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
	for (i = 0; i < arraylen; i++)
		cpu->ir[i] = 0;
	cpu->pc = 0;        
	cpu->running = 1;
}

// Read and dump initial values for memory
//
void readMemory(CPU *cpu) {
	int loc = 0;
	int i = 0;
	int j = 0;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");

	
        printf("Loc %02d: ", loc);
        scanf("%d", &cpu->mem[i]);
        loc++;
        i++;
        //tests to see if the location value  entered is valid
        while(cpu->mem[i-1] <= 9999 && cpu->mem[i-1] >= -9999){
                printf("Loc %02d: ", loc);
                scanf("%d", &cpu->mem[i]);
                loc++;
                i++;
        }
        //sets the remaining locations to zero
        for(j=0; j<100; j++){
                if(cpu->mem[j] > 9999 || cpu->mem[j] < -9999){
                        cpu->mem[j]= 0;
                }
        }

	printf("\nInitial value of memory:\n");
	dumpMemory(cpu);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(CPU *cpu) {
        // *** STUB *** Hint: How do printf formats %d, %5d, %-5d, %05d, and % 05d differ?
        int i;
        int j;
        int k=0;
        int location = 0;
        //for the first 5 rows(0-4)
        for(i=0; i<5; i++){
                if(cpu->reg[k] < 0){
                        printf("R%d:", location);
                        location++;
                        printf("%05d ", cpu->reg[k]);
                }
                else{
                        printf("R%d: ", location);
                        location++;
                        printf("%04d ", cpu->reg[k]);

                }
                k++;
        }
        printf("\n");
        //next 5 rows(5-9)
        for(j=5; j<10; j++){
                if(cpu->reg[k] < 0){
                        printf("R%d:", location);
                        location++;
                        printf("%05d ", cpu->reg[k]);
                }
                else{
                        printf("R%d: ", location);
                        location++;
                        printf("%04d ", cpu->reg[k]);
                }
                k++;
        }
        printf("\n");
}
// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.

void dumpMemory(CPU *cpu) {
        int i,j,q;
        int k = 0;
        int location = 0;

        for(i=0; i<10; i++){
                printf("%02d : ", location);
                //separated into two for-loops (one 0-4 and the other 5-9)
                //in order to put a space between each group of five columns.
                for(j=0; j<5; j++){
                        //if-statement is to test the sign
                        //of the number and add corresponding
                        //number of zeros so the columns line up
                        if(cpu->mem[k] < 0){
                                printf("%05d ", cpu->mem[k]);
                        }
                        else{
                                printf(" %04d ", cpu->mem[k]);
                        }
                        k++;
                }
                printf("   ");
                for(q=5; q<10; q++){
                        if(cpu->mem[k] < 0){
                                printf("%05d ", cpu->mem[k]);
                        }
                        else{
                                printf(" %04d ", cpu->mem[k]);
                        }
                        k++;

                }
                printf("\n");
                location += 10;
        }
}


// Execute one instruction cycle.
//


void instruction_cycle(CPU *cpu) {
        //set the value in the current memory location to number in order to break it up
        int number = cpu->mem[cpu->pc];
        int i;
        char input;
        if(number < 0)
                number = number * -1;
        //this for-loop breaks number into an array of length four
        for(i=3;i>=0;i--){
                cpu->ir[i] = number % 10;
                number /=10;
        }
        int op = cpu->ir[0];
        int r = cpu->ir[1];
        int mm =(cpu->ir[2] * 10) +  cpu->ir[3]; //combines the last two numbers of the number so that it becomes one integer

        switch(op){
                case 0 : printf("At %02d instruction %d  %d  %02d: HALT\n", cpu->pc, op, r, mm);
                         printf("\n HALTING\n");
                         cpu->running = 0;
                         break;
                case 1 : printf("At %02d instruction %d  %d  %02d: LD R%d <- M[%02d] = %d\n", cpu->pc, op, r, mm, r, mm, cpu->mem[mm]);
                         cpu->reg[r] = cpu->mem[mm];
                         break;
                case 2 : printf("At %02d instruction %d  %d  %02d: ST  M[%02d] <- R%d = %d\n", cpu->pc, op, r, mm, mm, r, cpu->reg[r]);
                         cpu->mem[mm] = cpu->reg[r];
                         break;
                case 3 : printf("At %02d instruction %d  %d  %02d: ADD  R%d <- R%d + M[%02d] = %d + %d = ", cpu->pc, op, r, mm, r, r,mm, cpu->reg[r], cpu->mem[mm]);                                           cpu->reg[r] = cpu->mem[mm] + cpu->reg[r];
                         //if-statement is used to test whether the value of regs[r] is within the memory range.
                         //if it is not, then it goes in the loop and gets truncated so that it is within the range
                         if(cpu->reg[r] > 9999 || cpu->reg[r] < -9999){
                                cpu->reg[r] = cpu->reg[r] % 10000;
                                printf("%d", cpu->reg[r]);
                                printf("\n");
                         }
                         else{
                                printf("%d", cpu->reg[r]);
                                printf("\n");
                         }
                         break;
                case 4 : printf("At %02d instruction %d  %d  %02d: NEG  R%d <- -R%d = %d\n", cpu->pc, op, r, mm, r, r, -cpu->reg[r]);
                         cpu->reg[r] = -cpu->reg[r];
                         break;
                case 5 : printf("At %02d instruction %d  %d  %02d: LDM  R%d <- %d\n", cpu->pc, op, r, mm, r, mm);
                         cpu->reg[r] = mm;
                         break;
                case 6 : printf("At %02d instruction %d  %d  %02d: ADDM  R%d <- R%d + %d = %d + %d = %d\n", cpu->pc, op, r, mm, r, r,  mm, cpu->reg[r], mm,  cpu->reg[r] + mm);
                         cpu->reg[r] = cpu->reg[r] + mm;
                         break;
                case 7 : printf("At %02d instruction %d  %d  %02d: BR %d\n", cpu->pc, op, r, mm, mm);
                         cpu->pc = mm - 1;
                         break;
                case 8 : printf("At %02d instruction %d  %d  %02d: BRP %d if R%d = %d > 0:", cpu->pc, op, r, mm, mm, r,cpu->reg[r]);
                         if(cpu->reg[r] > 0){
                                 printf(" yes");
                                 //reset pc to start at the instruction that we're branching to
                                 cpu->pc = mm - 1;
                                 printf("\n");
                         }
                         else{
                                 printf(" no");
                                 //once the program reaches instruction 99(pc = 99), the next instruction after that is 00, so we reset pc to equal 0
                                 if(cpu->pc == 99)
                                        cpu->pc = cpu->pc - 100;
                                 printf("\n");
                         }
                         break;
                case 9 : //test each case of op = 9 and do the corresponding instruction
                         if(r == 0){
                                 printf("At %02d instruction %d  %d  %02d: I/O Read char\n Enter a char (and press return): ", cpu->pc, op, r, mm);
                                 scanf("%c", &input);
                                 printf("R%d <- %d\n", r, input);
                                 cpu->reg[r] = input;
                                 scanf("%c", &input);
                                 break;
                         }
                         else if(r == 1){
                                 printf("At %02d instruction %d  %d  %02d: I/O %d: Print char in R%d (= %d): ", cpu->pc, op, r, mm,r, 0, cpu->reg[0]);
                                 printf("%c\n", cpu->reg[0]);
                                 break;
                         }
                         else if(r == 2){
                                 printf("At %02d instruction %d  %d  %02d: I/O %d: Print string: ",cpu->pc, op, r, mm, r);
                                 while(cpu->mem[mm] !=0){
                                         printf("%c", cpu->mem[mm]);
                                         mm++;
                                 }
                                 printf("\n");
                                 break;
                         }
                         else if(r == 3){
                                 printf("At %02d instruction %d  %d  %02d: I/O %d: Dump Registers\n", cpu->pc, op, r, mm, r);
                                 dumpRegisters(cpu);
                                 break;
                         }
                         else if(r == 4){
                                 printf("At %02d instruction %d  %d  %02d: I/O %d: Dump Memory\n", cpu->pc, op, r, mm, r);
                                 dumpMemory(cpu);
                                 break;
                         }
                         else{
                                 break;
                         }
        }
        cpu->pc++;
}

