// CS 350, Final Project, Fall 2013 (skeleton file)
// Jamal Kharrat
//
// LC3 simulator

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Basic Declarations
//
	typedef short int Word;
	typedef unsigned short int Address;

	#define MEMLEN 65536
	#define NBR_REGS 8

	typedef struct {
		Word memory[MEMLEN];
		Word reg[NBR_REGS];  // Note: "register" is a reserved word
		int condition_code;  // positive, zero, or negative
		Word instr_reg;		//CURRENT INSTRUCTION REGISTER :: IMPORTANT
		Address pgm_counter;	//PC Instruction counter
		int running;         // running = 1 iff CPU is executing instructions
	} CPU;


// Prototypes
//
	// CPU manipulation and status dump functions
	//
	void init_CPU(CPU *cpu);   // Simulate power-up
	void dump_CPU(CPU *cpu);
	void dump_control_unit(CPU *cpu);
	void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only);
	char get_condition_code(CPU *cpu);
	void set_condition_code(CPU *cpu, Word value);
	void dump_registers(CPU *cpu);
	void set_register(CPU *cpu, int regNbr, Word newValue);


	// Instruction cycle functions
	//

	void instruction_cycle(CPU *cpu);      // Simulate entire instruction cycle
	void fetch_instr(CPU *cpu);            // Simulate fetch instruction part of cycle
	// *** STUB *** You may want other routines (you may not)

	// Functions for accessing parts of an instruction
	//
	int op(Word w);                       // Opcode of an instruction
	// *** STUB *** You probably want other routines

	// Functions for executing each instruction
	//
	void instr_ADD (CPU *cpu);
	void instr_AND (CPU *cpu);
	void instr_BR  (CPU *cpu);
	void instr_err (CPU *cpu);
	void instr_JMP (CPU *cpu);
	void instr_JSR (CPU *cpu);
	void instr_LD  (CPU *cpu);
	void instr_LDI (CPU *cpu);
	void instr_LDR (CPU *cpu);
	void instr_LEA (CPU *cpu);
	void instr_NOT (CPU *cpu);
	void instr_RTI (CPU *cpu);
	void instr_ST  (CPU *cpu);
	void instr_STI (CPU *cpu);
	void instr_STR (CPU *cpu);
	void instr_TRAP(CPU *cpu);
	int  readchar();
	void printInf();             // TRAP reads a character for GETC, IN
	void helpMsg();



	int nonzero_only;
	Address _from;
	Address _to;

//Print infotmation about the Final Project
void printInf()
{
	printf("Jamal Kharrat Full LC-3 simulator\n");
	printf("File to read from:  ");
}
// -------------------- MAIN PROGRAM --------------------
//
// The main program creates and initializes a CPU, loads a program,
// and executes it step by step (until it halts or the user quits).
// The CPU is dumped before and after executing the program
//
int main() {
	// Create and initialize the  CPU, read initial memory, dump CPU
	//

	

	printInf();
	CPU cpu;
	init_CPU(&cpu);

	//Some declarations to read file
	char fileName [80];	//Char used to get the filename we want to scan
	char input =0;			//use input
	char prompt ="> ";	// prompt sign
			//FILE
	char memoryInput;
    int hex1, hex2;
	scanf("%s",fileName);

	FILE *iFile;
	iFile = fopen(fileName, "r");   //Reading from a file fopen 'r' mode
	printf("dddd\n");

	if (iFile == NULL)	//if file not found
	{
		perror ( fileName );
		printf("Possible file names:\n\nhelloworld.hex\nnegaddr.hex\nprintstring.hex\nrc.hex\nreadchar.hex\nreadstring.hex\n");
		// return 0;
		printf("File to read from:");
		scanf("%s",fileName);
		iFile = fopen(fileName, "r");
	}
	else
	{

		printf("*** Reading the contents of %s\n",fileName );	//print name of the file
		char line [128];		//an estimate how much chars in a file


		while (fgets (line, sizeof line, iFile) != NULL)	//READ THE FILE TILL THE END
		{
			fputs (line, stdout);	//STORE IT IN A LIKNE
		}
		fclose (iFile);
	}

	printf("\nInitial CPU: \n");

	//DUMP REGISTERS 
	dump_registers(&cpu);

	//
	//DUMP MEMORY
	dump_memory( &cpu, _to, _from,nonzero_only);

	printf("\nEnter command (h for help).\n");


	printf("%s\n",prompt );

	while (input != '\n' && getchar() != '\n')
	{
		// do nothing to clear from a char
	}

	scanf("%c",&input);

	do
	{
		while(input != '\n' && getchar() != '\n')
		{

		}

		switch (input)
		{
			case '\r':
			instruction_cycle(&cpu);
			printf("%s",prompt);
            scanf("%c",&input);
            break;

            case '\n':
            instruction_cycle(&cpu);
			printf("%s",prompt);
            scanf("%c",&input);
            break;

            case 'h':
            helpMsg();
            printf("%s",prompt);
            scanf("%c",&input);
            break;

            case 'q':
            printf("Quitting\n");
            break;

            case  'm':

            printf("\tm: ");
            scanf("%c", &memoryInput);
            printf("\thex_n1: ");
            scanf("%d", &hex1);
            printf("\thex_n1: ");
            scanf("%d", &hex2);
            
            while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
            printf("%s", prompt);
            scanf("%c", &input);
            break;

            default:

            printf("Unknown Cmd, ignored \n");
            printf("%s", prompt);
            scanf("%c", &input);

            break;

		}


	}
	while (input!= 'q');

	printf("Halting\n");









	/* *** STUB *** */
	return 0;


}

// -------------------- CPU ROUTINES --------------------
//
//



void helpMsg(void)
{
    printf("Commands:\n");
    printf("\th - Help\n");
    printf("\tq - Quit\n");
    printf("\td - Dump control unit\n");
    printf("\tm - hex_n1 hex_n2 - Dump memory values from hex_n1 - hex_n2\n");
  	printf("\tnbr - execute nbr of instructions\n");
    printf("\t(carriage return) - execute one instruction if CPU is running.\n");
  
}

	

// init_CPU(cpu) simulates power-on initialization: Program counter
// and instruction register are set to 0, as are memory and registers;
// condition code = Z, and the CPU will run the instruction cycle.
//
void init_CPU(CPU *cpu)
{
    cpu->pgm_counter = 0;
	cpu->instr_reg = 0;
	// *** STUB *** cpu->condition_code = ???;   // Z condition code on power-up
	cpu->running = 1;                // instruction cycle is running

	int regNbr;
	for (regNbr = 0; regNbr < NBR_REGS; regNbr++) {
		cpu->reg[regNbr] = 0;	// Fixed 2013-11-13
	}

	// Implementation note: You can't use a while loop
	// that checks for addr >= MEMLEN because addr is an
	// unsigned short and hence always <= MEMLEN.
	// (I.e., if addr = MEMLEN, then addr++ sets addr to 0.)
	//
	// In any case, we want the last word of memory to contain a HALT.
	//
	Address addr = 0;
	while (addr < MEMLEN-1) {
		cpu->memory[addr++] = 0;
	}
}


void set_register(CPU *cpu, int regNbr, Word newValue)
{

    
}

// -------------------- INSTRUCTION ROUTINES --------------------

// Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu) {
	cpu->instr_reg = cpu->memory[cpu->pgm_counter];
	cpu->pgm_counter = cpu->pgm_counter + 1;		// unsigned overflow will wraparound to 0
}

// Execute an instruction cycle
//   Fetch an instruction
//   Decode the instruction opcode
//   Execute the instruction
//
void instruction_cycle(CPU *cpu) {
	// Get current instruction to execute and its loc,
	// echo them out.
	//
	Address old_pc = cpu->pgm_counter;
	fetch_instr(cpu);
	printf("x%04hX: x%04hX  ", old_pc, cpu->instr_reg);

	// Execute instruction; set cpu running = 0 if CPU execution
	// is to stop (because of TRAP HALT or an internal error).
	//

	//>>>>>>>>>>>>>>>>SWITCH CASE MUST BE EDITED  Compliar error
	switch (cpu->instr_reg) {
	case  0: instr_BR(cpu);   break;
	/* *** STUB *** */

	default:
		printf("Bad opcode: %d; quitting\n", (cpu->instr_reg));
		cpu->running = 0;
	}
}

// Execute branch instruction: Bitwise AND instruction's mask and
// cpu's condition code, branch iff result is nonzero.
//
// Echo kind of branch, current cc, whether or not the branch happened,
// and if so, the target of the branch.
//
void instr_BR(CPU *cpu) {
	printf("BR instruction; *** STUB ***\n");
}

/* *** STUB *** */


// Read and return a character from standard input.  User must
// enter return after the char.  Just pressing return causes '\n'
// to be returned.  Any extra characters after the first are ignored.
//
int read_char() {
	char buffer[3] = "";
	fgets(buffer, sizeof buffer, stdin);
	return buffer[0];
}

void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only)
{
    int i = 3000;
    
    printf("(Nonzero) Memory from x0000 - xFFFF\n");
    for(i = 0; i < 10; i++)
    {
        printf("x%04x: x%04u ** Stub **\n", i, cpu->memory[i]);
        i++;
    }
}


void dump_registers(CPU *cpu)
{
    printf("PC = x%04d   IR = x%04d   CC = Z\n", cpu->reg[0], cpu->instr_reg);
	int i, j, loc = 0;
    for(i = 0; i < 4; i++)
    {
        printf("R%d ", loc);
        loc++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 4; j++)
    {
        printf("R%d ", loc);
        loc++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
        i++;
    }
    printf("\n");
    
}

/* *** STUB *** */
