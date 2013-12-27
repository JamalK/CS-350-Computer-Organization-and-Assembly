// CS 350, Final Project, Spring 2013 (skeleton file)
// LC3 simulator

// Andrey Danilkovich
// CS 350, Spring 2013
// Illinois Institute of Technology, (c) 2013

/* Program Description
 
 Little Computer 3, or LC-3, is a type of computer educational programming language, 
 an assembly language, which is a type of low-level programming language.
 
 It features a relatively simple instruction set, but can be used to write moderately complex assembly programs, 
 and is a theoretically viable target for a C compiler. The language is less complex than x86 assembly but has 
 many features similar to those in more complex languages.
 
*/

// Notes: Extra credit - validate input, give options, ask user for another input
//        Extra credit 2 - Print instructions
//        Extra credit 3 - case sensitive

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

 short unsigned int orig;
 short unsigned int u_reg;

 // Second structure for the commands of the opcode.
 // Analysis of bit strings
  struct Commands{
    unsigned short opCode;      // **** 0000 0000 0000
    unsigned short intSecond;   // 0000 **** 0000 0000
    unsigned short NZP ;        // 000* **00 0000 0000
    unsigned short offset;      // 0000 **** **** ****
    unsigned short trap;        // 0000 0000 **** ****
    unsigned short last;        // 0000 0000 0000 ****
    unsigned short intRest;     // helps with trap
      
    unsigned short Src1;
    unsigned short Base;
    unsigned short Src2;
    unsigned short immed;
      
 } Commands;


 // Prototypes
 //
 // CPU manipulation functions
 //
 void init_CPU(CPU *cpu);
 Word get_memory(CPU *cpu, Address addr);
 void set_memory(CPU *cpu, Address addr, Word value);
 void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only, int counter);

 Word get_register(CPU *cpu, int regNbr);
 void set_register(CPU *cpu, int regNbr, Word newValue);
 void dump_registers(CPU *cpu);

 char get_condition_code(CPU *cpu);
 void set_condition_code(CPU *cpu, Word value);
 
 // Instruction cycle functions
 //
 void fetch_instr(CPU *cpu);
 void instruction_cycle(CPU *cpu , int order);
 
 // Functions for executing each instruction.
 // TRAP uses readchar() to read a character (GETC, IN).
 //
 void instr_ADD (CPU *cpu);
 void instr_AND (CPU *cpu);
 void instr_BR  (CPU *cpu);
 void instr_err (CPU *cpu);
 void instr_JMP (CPU *cpu);
 void instr_JSR (CPU *cpu);
 void instr_LD  (CPU *cpu, int order);
 void instr_LDI (CPU *cpu);
 void instr_LDR (CPU *cpu);
 void instr_LEA (CPU *cpu, int order);
 void instr_NOT (CPU *cpu);
 void instr_RTI (CPU *cpu);
 void instr_ST  (CPU *cpu, int order);
 void instr_STI (CPU *cpu);
 void instr_STR (CPU *cpu);
 void instr_TRAP(CPU *cpu);
 int  readchar();  // For GETC, IN

 // ADDITIONAL HELPER FUNCTIONS
 // Program messages
 //
 void helpMsg(void);
 void description(void);
 void setMemory(CPU *cpu);

 int getfirst(CPU *cpu, int counter);
 int getsecond(CPU *cpu, int counter);
 int getrest(CPU *cpu, int counter);


int main()
{
	// Declare and initialize the CPU
    CPU cpu;
    init_CPU(&cpu);
    
    //char filename[80];
    char input = 0;
    char prompt[] = "> ";
    
    int counter;        // how many values read from file
    int addr  = 0;
    
    description();  // Call display name and project
    counter = get_memory(&cpu, addr);   // Call function
    
    printf("\nInitial CPU:\n");    
    dump_registers(&cpu);   // Call dump registers function
    
    dump_memory(&cpu, to, from, nonzero_only, counter);
    printf("\n");
    
    
    printf("Beginning execution:\nAt the > prompt, press return to execute the next instruction, q to quit,\nr to dump the registers, m hex#1 hex#2 to dump memory, or h for help.\n");

	printf("%s", prompt);
    
    while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
    scanf("%c", &input);
    
    int order = (cpu).memory[0];        // set order for instrction cycle
    
	do
    {
        while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
        
        if(input == '\r' | input == '\n')
        {
            instruction_cycle(&cpu, order);
            printf("%s", prompt);
            scanf("%c", &input);
            order++;
        }
        else if(input == 'h')
        {
            helpMsg();              // call help message
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if (input == 'r')
        {
            printf("Dump registers\n");
            dump_registers(&cpu);
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else if(input == 'q')
        {
            printf("Quitting\n");
        }
        else if (input == 'm')
        {
            char s[] = "m 01f  359a";
            sscanf(s, "m %hx %hx", &from, &to);
            dump_memory(&cpu, to, from, nonzero_only, counter);
            printf("%s", prompt);
            scanf("%c", &input);
        }
        else
        {
            printf("Unknown command; ignoring it.\n");
            helpMsg();              // call help message
            printf("%s", prompt);
            scanf("%c", &input);
        }
        
    }
    while (input != 'q');  // End loop when user enters q. Previous command - & cpu->pc != 100
    
    printf("Quitting\n");
    printf("Halting\n");
    
    // Final step - Dump registers and Memory
    dump_registers(&cpu);
    dump_memory(&cpu, to, from, nonzero_only, counter);
	return 0;
}

// Display name and project
//
void description()
{
    printf("CS 350 Final Project, Andrey Danilkovich\nLC3 Simulator\n\n");
    printf("File to read from: ");
}

// Function to show possible commands when running the Instruction Cycle
// 
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
    cpu->condition_code = 0;        // Z condition code on power-up
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
    char filename[80];
    char compare[4] = "0000"; // Compare and ignore 0000 from input
    int count = 0;
    int test1 = 0; // Test to input the file
    
    while (test1 != 1)
    {
        scanf("%s", filename);
        FILE *file = fopen ( filename, "r" );
        if ( file != NULL )
        {
            printf("Reading from %s \n", filename);
            char line [ 128 ]; /* or other suitable maximum line size */
            while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
            {
                /* Test: Write lines
                 fputs ( line, stdout );  //write the line
                 */
            
                //Sample: sscanf(str, "%s %s %s %s", el->field1, el->field2, el->field3, el->field4);
                sscanf(line, "%hx", &cpu->memory[addr]);
                addr++;
                if( strcmp(line,compare) != 0 )
                    count++;
            }
            fclose ( file );
            test1 = 1;
        }
        else
        {
            perror ( filename ); /* why didn't the file open? */
        
            printf("Possible file names:\n\nhelloworld.hex\nnegaddr.hex\nprintstring.hex\nrc.hex\nreadchar.hex\nreadstring.hex\n");

            printf("\nFile to read from: ");
            //scanf("%s", filename);
        
            test1 = 0;
        }
    }
    return count;
    // return cpu->memory[addr];
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

// Display what is located in memory.
// Part of CPU structure.
//
void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only, int counter)
{
    int m = 0, i, j = 0, k = 1;
    int end = counter + cpu->memory[0];
    int count = 0;
    char *code = NULL;
    
    
    for(m = 0; m <= counter; m++)
    {
        if(cpu->memory[m+1] == 0)
        {
            end --;
        }
    }
    
    printf("(Nonzero) Memory from x0000 - xFFFF\n");
    for(i = cpu->memory[j]; i <= end; i++)
    {
        // IF Condition: place correct first memmory and increment couter
        if(cpu->memory[0] == i)
        {
            count ++;
        }
        
        Address old_pc = cpu->memory[0+k]; // OLD: cpu->pgm_counter
        Commands.opCode = (old_pc >> 12); // Finished
        
        // Handle the zeros; don't print them.
        if(cpu->memory[count] != (unsigned short)'0')
        {
            if(Commands.opCode == 0){
                char OP[] = "BR";
                code = OP;
            }
            
            if(Commands.opCode == 1){
                char OP[] = "ADD";
                code = OP;
            }
            if(Commands.opCode == 2){
                char OP[] = "LD";
                code = OP;
            }
            if(Commands.opCode == 3){
                char OP[] = "ST";
                code = OP;
            }
            if(Commands.opCode == 4){
                char OP[] = "JSR";
                code = OP;
            }
            if(Commands.opCode == 5){
                char OP[] = "AND";
                code = OP;
            }
            if(Commands.opCode == 6){
                char OP[] = "LDR";
                code = OP;
            }
            if(Commands.opCode == 7){
                char OP[] = "STR";
                code = OP;
            }
            if(Commands.opCode == 8){
                char OP[] = "RTI";
                code = OP;
            }
            if(Commands.opCode == 9){
                char OP[] = "NOT";
                code = OP;
            }
            if(Commands.opCode == 10){
                char OP[] = "LDI";
                code = OP;
            }
            if(Commands.opCode == 11){
                char OP[] = "STI";
                code = OP;
            }
            if(Commands.opCode == 12){
                char OP[] = "JMP";
                code = OP;
            }
            if(Commands.opCode == 13){
                char OP[] = "err";
                code = OP;
            }
            if(Commands.opCode == 14){
                char OP[] = "LEA";
                code = OP;
            }
            if(Commands.opCode == 15){
                char OP[] = "TRAP";
                code = OP;
            }
            
            printf("x%04X: x%04hX %8d   %s\n", i, cpu->memory[count], cpu->memory[count], code);
            count++;
            k++;
            
        }
        j++;
    }
}

// Dump the registers. Use for loops to display rows
//
void dump_registers(CPU *cpu)
{
    printf("PC = x%04X   IR = x%04hX   CC = Z\n", (cpu->memory[0] + cpu->pgm_counter), cpu->instr_reg);
    // cpu->reg[r]
	int i, j, location = 0;
    //first row 0 - 5
    for(i = 0; i < 4; i++)
    {
        printf("R%d ", location);
        location++;
        printf("x%04hX  %-8d", cpu->reg[i], cpu->reg[i]);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 5; j < 9; j++)
    {
        printf("R%d ", location);
        location++;
        printf("x%04hX  %-8d", cpu->reg[j], cpu->reg[j]);
    }
    printf("\n");
    
}

void instruction_cycle(CPU *cpu, int order)
{
 // Get current instruction to execute and its location,
 // echo them out.
 //
    Address old_pc = cpu->memory[cpu->pgm_counter+1]; // OLD: cpu->pgm_counter
    fetch_instr(cpu);
    
    int op_code = 0;
    u_reg = ((unsigned short int)(cpu->instr_reg));
	op_code = u_reg/4096;
    
    unsigned short movement1 = (old_pc << 4);
    unsigned short movement2 = (old_pc << 7);
    unsigned short movement3 = (old_pc << 12);
    unsigned short movement4 = (old_pc << 7);
    unsigned short movement5 = (old_pc << 13);
    
    Commands.opCode = (old_pc >> 12); // Finished
    
    Commands.intRest =  (old_pc << 8); // Finished
    Commands.trap = (Commands.intRest >> 8); // Finished
    
    Commands.NZP    =   (movement1 >> 13);
    Commands.offset =   (movement2 >> 7);
    Commands.last   =   (movement3 >> 12);
    Commands.Src1   =   (movement4 >> 6);
    Commands.Src2   =   (movement5 >> 13);
    
    
    /* Tests
     
    Output bit shifts
     
     
    printf("\nShowing whats in memory, dividing integers:\n\n");
    printf("First Hex: %hX\n", Commands.opCode);
    printf("Second Hex: %hX\n", Commands.intSecond);
    //printf("Remaining Hex: %hX\n", intRest);
    printf("NZP value: %hX\n", Commands.NZP);
    printf("offset value: %hX\n", Commands.offset);
    printf("Trap value (last 2 digits): %hX\n", Commands.trap);
    printf("Last value: %hX\n", Commands.last);
    */
     
    
 // Execute instruction; set halt = 1 if execution is to stop
 // (TRAP HALT or internal error).
 //
    switch ((Commands.opCode)) // ** Note ** place "op(cpu->instr_reg))"
    {
        case  0:
            if (Commands.NZP > 0){
                // Command loop that accounts for P and Z
                // Removed because of the lack of time
                
                /*if(Commands.NZP == 2){
                    printf("BRZ  3, CC = P, no go to\n");
                    //cpu->pgm_counter--;
                }
                else{ */
                order ++;
                printf("x%04X: x%04hX  ", order, old_pc);   // print location
                cpu->pgm_counter = cpu->pgm_counter + Commands.last;
                printf("BR   %d, CC = Z, go to x%04X+%d = x%04X\n", Commands.last, order, (signed short)Commands.last, (order + Commands.last));
                order = order + Commands.last;
            }
            else{
            instr_BR(cpu);
            }
            break;
            
        case 1:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_ADD(cpu);
            break;
            
        case 2:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_LD(cpu, order);
            break;
            
        case 3:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_ST(cpu, order);
            break;
            
        case 4:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_JSR(cpu);
            break;
            
        case 5:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_AND(cpu);
            break;
            
        case 6:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_LDR(cpu);
            break;
            
        case 7:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_STR(cpu);
            break;
            
        case 8:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_RTI(cpu);
            break;
            
        case 9:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_NOT(cpu);
            break;
            
        case 10:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_LDI(cpu);
            break;
            
        case 11:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_STI(cpu);
            break;
            
        case 12:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_JMP(cpu);
            break;
            
        case 13:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_err(cpu);
            break;
            
        case 14:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_LEA(cpu, order);
            break;
            
        case 15:
            printf("x%04X: x%04hX  ", order, old_pc);
            instr_TRAP(cpu);
            break;
            
            
        default:
            printf("Bad opcode: %d; quitting\n", (Commands.opCode)); // ** Note ** place "op(cpu->instr_reg))"
            cpu->running = 0;
    }
    old_pc++;
    
}
 
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

// -------------------- INSTRUCTIONS --------------------
//
// Execute branch instruction: Bitwise AND instruction's mask and
// cpu's condition code, branch iff result is nonzero.
//
// Echo kind of branch, current cc, whether or not branch happened,
// and if so, the target of the branch.
//


// -------------------- BR --------------------
// NOTE: HANDLED IN INSTRUCTION CYCLE!!
// Prints message when 9bit offset is zero.
void instr_BR(CPU *cpu)
{
    printf("CPU is not running.\n");
    cpu->pgm_counter--; // decrement program counter because CPU is not running
}

// -------------------- LD --------------------
//
void instr_LD(CPU *cpu, int order)
{
    /*
     int mem_offset = u_reg % 256;
     int dst = (u_reg/512) % 8;
     printf("\nR%d <- M[x%04hX]\n", dst, mem_offset + cpu->pgm_counter);
     cpu->reg[dst] = cpu->memory[cpu->pgm_counter + mem_offset];
     */
    
    cpu->reg[Commands.NZP] = order + Commands.offset ;
    printf("LD  R%d, %d;  R%d <- M[PC+%d] = M[x%X] = x%X; CC = P\n",
           Commands.NZP, Commands.offset, Commands.NZP, Commands.offset,
           cpu->reg[Commands.NZP]+1, cpu->reg[Commands.NZP]); //x7FF0: x200F
}

// -------------------- ADD --------------------

// ADD 0001  Dst  Src1 0 00 Src2
void instr_ADD(CPU *cpu)
{
    // Old definition
    int src1 = (u_reg/64) % 8;
    int src2 = (u_reg/128) % 8;
    int Immed5 = src1 % 256;
    
    src1 = Commands.Src1;
    src2 = Commands.Src2;
    Immed5 = Commands.Base;
    
    printf("ADD  R%d, R%d, %d;  R%d <- x%X+%d = x%X; CC = P\n",
           Commands.NZP, Commands.Src2, Commands.NZP, Commands.NZP, cpu->reg[Commands.NZP], Commands.Src2, cpu->reg[Commands.NZP] +Commands.Src2); // x3007: x14A1
    
    // ADD Logic
    // ADD 0001  Dst  Src1 0 00 Src2
    cpu->reg[Commands.NZP] = cpu->reg[Commands.NZP] + cpu->reg[Commands.Src2];

}

// -------------------- AND --------------------
// DST SRC1 (1 or 0) Immed
// AND 0101  Dst Src1 0 00 Src2
void instr_AND(CPU *cpu)
{
    // Old definition
    int src1 = (u_reg/64) % 8;
    int src2 = (u_reg/128) % 8;
    int Immed5 = src1 % 256;
    
    src1 = Commands.Src1;
    src2 = Commands.Src2;
    Immed5 = Commands.Base;
    cpu->reg[Commands.NZP] = Commands.intSecond & Commands.intRest;
    
    
    printf("AND  R%d, R%d, %d;  R%d <- x0000 & x0000 = x0; CC = Z\n",
           Commands.NZP, Commands.NZP, Commands.NZP, Commands.last); //x7FFA: x5B60
    
    // AND Logic
    // AND 0101  Dst Src1 0 00 Src2
    cpu->reg[Commands.NZP] = cpu->reg[Commands.NZP] & cpu->reg[Commands.Src2];
}

// -------------------- ERR --------------------
// err   Don'tCare12 
void instr_err(CPU *cpu)
{
    cpu->memory[cpu->pgm_counter] = Commands.intRest & 000000000000;
    printf("ERR  Don'tCare 12  Op code unused, Halting\n");
}

// -------------------- JMP --------------------
// The value in the base register is used as the new PC value;
// i.e., we go to the address indicated by the base register
void instr_JMP(CPU *cpu)
{
    cpu->reg[Commands.NZP] = Commands.trap;
    printf("JMP R%d < - x%X\n", Commands.NZP, cpu->reg[Commands.NZP]);
}

// -------------------- JSR --------------------
// JSR  4 0100 1 PCoffset11
void instr_JSR(CPU *cpu)
{
    cpu->reg[cpu->pgm_counter] = cpu->reg[cpu->pgm_counter]+ Commands.last;
    printf("JSR R%d, %d;  R%d <- PC+%d = x%X; CC = P\n", Commands.NZP, Commands.offset, Commands.offset, Commands.offset,cpu->reg[Commands.NZP]);
}

// -------------------- LDI --------------------
//
void instr_LDI(CPU *cpu)
{
    //printf("LDI  R4, 9;  R4 <- M[M[PC+9]] = M[M[x8002]]= M[x8000]  = x7FFF; CC = P\n"); // x7FF8: xA809
    
    int mem_offset = u_reg % 256;
	int dst = ((cpu->instr_reg)/512) % 8;
	printf("LDI R%d <- M[M[x%04X]]\n", dst, mem_offset + cpu->pgm_counter);
	cpu->reg[dst] = cpu->memory[cpu->memory[cpu->pgm_counter + mem_offset]];
}

// -------------------- LDR --------------------
//
void instr_LDR(CPU *cpu)
{
    //printf("LDR  R2, R1, 0;  R2 <- M[x8000+0] = M[x8000] = x7FFF; CC = P\n"); // x7FF4: x6440
    
    int immed = u_reg % 256;
	int dst = (u_reg/512) % 8;
	int src = (u_reg/64) % 8;
	printf("LDR R%04X <- R%04X + x%04X\n", dst, src, immed);
	cpu->reg[dst] = cpu->reg[src] + immed;
}

// -------------------- LEA --------------------
//
void instr_LEA(CPU *cpu, int order)    // Done
{
    cpu->reg[Commands.NZP] = order + Commands.offset + 1;
    
    printf("LEA  R%d, %d;  R%d <- PC+%d = x%X; CC = P\n", Commands.NZP, Commands.offset, Commands.offset, Commands.offset,cpu->reg[Commands.NZP]); //x3000: xE002
}

// -------------------- NOT --------------------
//
void instr_NOT(CPU *cpu)
{
    int dst = ((cpu->instr_reg)/512)%8;
    int src = ((cpu->instr_reg)/64)%8;
    //printf("NOT R%d <- -R%d", dst, src);
    
    Word not = ~(cpu->reg[Commands.NZP]);
    
    printf("NOT  R%d, R%d;  R%d <- NOT x%X = x%X; CC = N\n",
           Commands.NZP, Commands.NZP, Commands.NZP, cpu->reg[Commands.NZP], not); // x3004: x94BF
    cpu->reg[dst] = -cpu->reg[src];
}

// -------------------- RTI --------------------
//
void instr_RTI(CPU *cpu)
{
    cpu->reg[Commands.NZP] = 0;
    printf("RTI R%d, R%d;  R%d <- NOT x%X; CC = N\n",
           Commands.NZP, Commands.NZP, Commands.NZP, cpu->reg[Commands.NZP]);
}

// -------------------- ST --------------------
//
void instr_ST(CPU *cpu, int order)
{
    //printf("ST Instruction\n");
    
    /*
    int mem_offset = (cpu->instr_reg)% 256;
    int src = ((cpu->instr_reg)/512)%8;
    printf("\nM[x%04hX] <- R%d\n", cpu->pgm_counter + mem_offset, src);
    cpu->memory[cpu->pgm_counter + mem_offset] = cpu->reg[src];
     
     */
    cpu->reg[Commands.NZP] = order+Commands.offset;
    
    printf("ST R%d, %d;  M[PC+%d] = M[x%X] <- x%X\n",
           Commands.NZP, Commands.offset, Commands.offset, cpu->memory[cpu->pgm_counter], cpu->pgm_counter + 1); // x7FF1: x31E0
}

// -------------------- STI --------------------
//
void instr_STI(CPU *cpu)
{
    //printf("STI  R4, 6;  M[M[PC+6]] = M[M[x8000]]= M[x7FFF] <- x7FFF\n"); // x7FF9: xB806
    
    int mem_offset = (u_reg) % 256;
	int src = (u_reg/512) % 8;
	printf("STI R%d <- x%04X\n", src, mem_offset);
	cpu->reg[src] = mem_offset;
    
}

// -------------------- STR --------------------
//
void instr_STR(CPU *cpu)
{
    int mem_offset = (u_reg) % 64;
	int dst = (u_reg/512) % 8;
	int src = (u_reg/64) % 8;
    printf("STR  R%d, R%d, %d;  M[x%X-%d] = M[x7FE0] <- x7FFF\n",
           Commands.NZP, src, Commands.trap, cpu->reg[src], Commands.trap); //x7FF5: x7460
	//printf("STR R%d, R%d, Rx%04hX <- R%d + %04hX\n", Commands.NZP, src, dst, src, mem_offset);
	cpu->reg[dst] = cpu->reg[src] + mem_offset;
        
}

// -------------------- TRAP --------------------
//
/*
// Trap Vectors
// x20 - GETC Read character from keyboard into R0[7..0]; clear R0[15..8].
// x21 - OUT Print Characer in R0
// x22 - PUTS - Print string of ASCII chars
// x23 - IN - Like x20 but prints a prompt on the screen first.
// x24 - PUTSP prints 2 characters
// x25 - HALT - Halt execution
 */
void instr_TRAP(CPU *cpu)
{
    if(Commands.trap == 14 | Commands.trap ==  32)      // x20 TRAP
    // Read character from keyboard into R0[7..0]; clear R0[15..8].
    {
        char input;
        printf("TRAP x20 (GETC): [type char & return (or just press return)] ");
        input = read_char();
        printf("Read <%c> = %d\n", input, input);
        cpu->reg[0]= 0;
    }
    if(Commands.trap == 15 | Commands.trap ==  33)      // x21 TRAP
    // Print character in R0[7..0]
    {
        char input = 'a';
        printf("TRAP x21 (OUT): %d = %c\n", input, input);
    }
    if(Commands.trap == 16 | Commands.trap ==  34)      // x22 TRAP
    {
        printf("TRAP x22 (PUTS): Enter chars (return to halt:) \n");
        /* IDEA
         
         while(cpu->mem[intRest] !=0){
            printf("%c", cpu->mem[intRest]);
            intRest++;
        }
        printf("\n");
          END IDEA
         */
    }
    if(Commands.trap == 17 | Commands.trap ==  35)      // x23 TRAP
    {
        char input;
        printf("TRAP x23 Input a character > ");
        input = read_char();
        printf("(IN): %d = %c\n", input, input);
        
        cpu->reg[0]= input;
    }
    if(Commands.trap == 18 | Commands.trap ==  36)      // x24 TRAP
    {
        printf("TRAP x20 (GETC): [type char & return (or just press return)] \n");
    }
    if(Commands.trap == 19 | Commands.trap ==  37)      // x25 TRAP
    {
        printf("TRAP x25 Halting\n");
        cpu->reg[8] = (cpu->memory[0] + cpu->pgm_counter);
    }
}

