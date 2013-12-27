// CS 350, Final Project, Spring 2013 (skeleton file)
//
// LC3 simulator

#include <stdio.h>
#include <string.h>
#include <math.h>
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
 int condition_code;  // 1=positive, 2=zero, 3=negative
 Word instr_reg;
 Address pgm_counter;
 int running;         // running = 1 iff CPU is executing instructions
 } CPU;
 
 Address from;
 Address to;
 int nonzero_only;


 // Prototypes
 //
 // CPU manipulation functions
 //

 void init_CPU(CPU *cpu);


 Word get_memory(CPU *cpu, Address addr);
 void set_memory(CPU *cpu, Address addr, Word value);
 void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only);

 Word get_register(CPU *cpu, int regNbr);
 void set_register(CPU *cpu, int regNbr, Word newValue);
 void dump_registers(CPU *cpu);

 char get_condition_code(CPU *cpu);
 void set_condition_code(CPU *cpu, Word value);
 
 // Instruction cycle functions
 //
 void fetch_instr(CPU *cpu);
 void instruction_cycle(CPU *cpu);
 
 // Functions for executing each instruction.
 // TRAP uses readchar() to read a character (GETC, IN).
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
 int  readchar();  // For GETC, IN
 
 void helpMsg(void);

 // -------------------- MAIN PROGRAM --------------------
 //


int main()
{
	// Declare and initialize the CPU
	// ..
    CPU cpu;
    init_CPU(&cpu);
    // ..   
    
    printf("CS 350 Final Project, Andrey Danilkovich\nLC3 Simulator\n\n");
    printf("File to read from: ");
    
    
    char filename[80];
    char input = 0;
    char prompt[] = "> ";
    
    char memoryInput;
    int hex1, hex2;
    
    
    scanf("%s", filename);
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        printf("** %s contains **\n\n", filename);
        char line [ 128 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
        {
            fputs ( line, stdout ); /* write the line */
        }
        fclose ( file );
    }
    else
    {
        perror ( filename ); /* why didn't the file open? */
        
        printf("Possible file names:\n\nhelloworld.hex\nnegaddr.hex\nprintstring.hex\nrc.hex\nreadchar.hex\nreadstring.hex\n");
        
        return 0;
        printf("\nFile to read from: ");
        scanf("%s", filename);
        
    }

    printf("\nInitial CPU:\n");    
    dump_registers(&cpu);
    
    dump_memory(&cpu, to, from, nonzero_only);
    printf("\n");
    
    
    printf("Beginning execution:\nAt the > prompt, press return to execute the next instruction, q to quit,\nr to dump the registers, m hex#1 hex#2 to dump memory, or h for help.\n");
    

	printf("%s", prompt);
    
    while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
    scanf("%c", &input);
    
    
	do
    {
        while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
        
        if(input == '\r' | input == '\n')
        {
            instruction_cycle(&cpu);
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if(input == 'h')
        {
            helpMsg();              // call help message
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if (input == 'r')
        {
            printf("*** STUB *** Dump registers\n");
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if(input == 'q')
        {
            printf("Quitting\n");
        }
        else if (input == 'm')
        {
            printf("\tm: ");
            scanf("%c", &memoryInput);
            printf("\thex_n1: ");
            scanf("%d", &hex1);
            printf("\thex_n1: ");
            scanf("%d", &hex2);
            
            while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else
        {
            printf("Unknown command; ignoring it.\n");
            printf("%s", prompt);
            scanf("%c", &input);
        }
        
    }
    while (input != 'q');  // & cpu->pc != 100
    
    printf("Halting\n");
    
	return 0;
}

void helpMsg(void)
{
    printf("Commands:\n");
    printf("\th - Help\n");
    printf("\tq - Quit\n");
    printf("\tr - Dump registers\n");
    printf("\tm - mem hex_n1 hex_n2 - Dump memory values from hex_n1 - hex_n2\n");
    printf("\t(carriage return) - execute one instruction if CPU is running.\n");
  
}

// -------------------- CPU ROUTINES --------------------
//
//
void init_CPU(CPU *cpu)
{
    cpu->pgm_counter = 0;
    cpu->instr_reg = 0;
    cpu->condition_code = 0; //** STUB **;  // Z condition code on power-up
    cpu->running = 1;               // CPU is running
 
    int regNbr = 0;
    while (regNbr < NBR_REGS)
    {
        set_register(cpu, regNbr++, 0);
    }
 
    Address addr = 0;
    do
    {
        cpu->memory[addr++] = 0;
    }
    while (addr > 0);
}

void set_register(CPU *cpu, int regNbr, Word newValue)
{
    /* Do Something */
    
}


// -------------------- MEMORY ROUTINES --------------------
//
// get_memory(cpu, addr) returns the Word at the cpu's memory address
//
Word get_memory(CPU *cpu, Address addr)
{
    return cpu->memory[addr];
}
 
 // set_memory(cpu, addr, value) copies the value to the cpu's memory address
 //
void set_memory(CPU *cpu, Address addr, Word value)
{
    cpu->memory[addr] = value;
}
 

//   Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu)
{
    cpu->instr_reg = cpu->memory[cpu->pgm_counter];
    cpu->pgm_counter = (cpu->pgm_counter + 1) % MEMLEN;
}
 
//   Execute an instruction cycle
//   Fetch an instruction
//   Decode the instruction opcode
//   Execute the instruction
//
void instruction_cycle(CPU *cpu)
{
 // Get current instruction to execute and its location,
 // echo them out.
 //
    Address old_pc = cpu->pgm_counter;
    fetch_instr(cpu);
    printf("x%04hX: x%04hX  ", old_pc, cpu->instr_reg);
 
 // Execute instruction; set halt = 1 if execution is to stop
 // (TRAP HALT or internal error).
 //
    switch ((cpu->instr_reg)) // ** Note ** place "op(cpu->instr_reg))"
    {
        case  0:
            instr_BR(cpu);
            break;

 
        default:
            printf("Bad opcode: %d; quitting\n", (cpu->instr_reg)); // ** Note ** place "op(cpu->instr_reg))"
            cpu->running = 0;
    }
}
 
 // Execute branch instruction: Bitwise AND instruction's mask and
 // cpu's condition code, branch iff result is nonzero.
 //
 // Echo kind of branch, current cc, whether or not branch happened,
 // and if so, the target of the branch.
 //

void instr_BR(CPU *cpu)
{
    printf("BR instruction; *** STUB ***\n");
}
 
/*** STUB ***/

 
// Read and return a character from standard input.  User must
// enter return after the char.  Just pressing return causes \n
// to be returned.  Any extra characters after the first are ignored.
//
int read_char()
{
    char buffer[3] = "";
    fgets(buffer, sizeof buffer, stdin);
    return buffer[0];
}
 
 /*** STUB ***/

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
    // cpu->reg[r]
	int i, j, location = 0;
    //first row 0 - 5
    for(i = 0; i < 4; i++)
    {
        printf("R%d ", location);
        location++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 4; j++)
    {
        printf("R%d ", location);
        location++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
        i++;
    }
    printf("\n");
    
}
