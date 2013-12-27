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
Word get_register(CPU *cpu, int regNbr);
void set_register(CPU *cpu, int regNbr, Word newValue);
void set_memory(CPU *cpu, Address addr, Word value);
Word get_memory(CPU *cpu, Address addr);
int bitshift(Word content,int left,int right,int needsign);
int power2(int point);


// Instruction cycle functions
//

void instruction_cycle(CPU *cpu);      // Simulate entire instruction cycle
void fetch_instr(CPU *cpu);            // Simulate fetch instruction part of cycle
// *** STUB *** You may want other routines (you may not)

// Functions for accessing parts of an instruction
//
Word op(Word w);                       // Opcode of an instruction
// *** STUB *** You probably want other routines

// Functions for executing each instruction
//
Address readfile(CPU *cpu);
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

Address readfile(CPU *cpu){
    char fname[100];
    scanf("%s",fname);
    FILE *f;
    unsigned int num[80];
    
    f=fopen(fname,"r");
    while (f==NULL){
        printf("\nfile doesnt exist?!\n");
        printf("name of file?：");
        scanf("%s",fname);
        f=fopen(fname,"r");
    }
    unsigned int temp =0;
    fscanf(f,"%x",&temp);
    cpu->pgm_counter = temp;
    int i = temp;
    cpu->memory[i] = temp;
    Address end = 0;
    while (fscanf(f,"%x",&temp) != EOF){
        cpu->memory[i] = temp;
        i++;
        end++;
    }
    end +=cpu->pgm_counter;
    fclose(f);
    end--;
    printf("PGM COUNTER %d \n END %d", cpu->pgm_counter,end );
    return end;
}



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
	char prompt [10] ="> ";	// prompt sign
    //FILE
	char memoryInput;
    int hex1, hex2;
    
    
    
    int end = readfile(&cpu);
    int orig = cpu.pgm_counter;
    
    
	// printf("PGM COUNTER %d \n END %d", cpu.pgm_counter,end );
    
	dump_registers(&cpu);
    
	dump_memory(&cpu,orig,end,0);
	
    
	printf("\nInitial CPU: \n");
    
	//DUMP REGISTERS
	// dump_registers(&cpu);
    
	//
	//DUMP MEMORY
	// dump_memory( &cpu, _to, _from,nonzero_only);
    
    
    
	printf("\nEnter command (h for help).\n");
    
    char command[80];
    fgets(command, sizeof command, stdin);
    while(cpu.running==1){
        printf("%s", prompt);
        fgets(command, sizeof command, stdin);                // Read past end of current line.
        char op = command[0];
        unsigned int from=0;
        unsigned int too = 0;
        switch(op){
            case 'q':
                cpu.running = 0;
                break;
            case 'h':
                helpMsg();
                break;
            case '?':
                helpMsg();
                break;
            case 'd':
                dump_control_unit(&cpu);
                printf("%s",prompt);
                scanf("%c",&input);
                break;
            case 'm':
                sscanf(command,"m %x %x",&from,&too);
                dump_memory(&cpu,(Address)from,(Address)too,0);
                break;
            default:
                instruction_cycle(&cpu);
                break;
        }
    }
    
    
    
	// printf("%s",prompt);
    
    
	// while (input != '\n' && getchar() != '\n')
	// {
	// 	// do nothing to clear from a char
	// }
    
	// scanf("%c",&input);
    
	// do
	// {
	// 	while(input != '\n' && getchar() != '\n')
	// 	{
    
	// 	}
    
	// 	switch (input)
	// 	{
	// 		case '\r':
	// 		// instruction_cycle(&cpu);
	// 		printf("%s",prompt);
    //            scanf("%c",&input);
    //            break;
    
    //            case '\n':
    //            // instruction_cycle(&cpu);
	// 		printf("%s",prompt);
    //            scanf("%c",&input);
    //            break;
    
    //            case 'h':
    //            helpMsg();
    //            printf("%s",prompt);
    //            scanf("%c",&input);
    //            break;
    
    //            case 'd':
    //            dump_control_unit(&cpu);
    //            printf("%s",prompt);
    //            scanf("%c",&input);
    //            break;
    
    //            case 'q':
    //            cpu.running=0;
    //            printf("Quitting\n");
    //            break;
    
    //            case  'm':
    
    //            printf("\tm: ");
    //            scanf("%c", &memoryInput);
    //            printf("\thex_n1: ");
    //            scanf("%d", &hex1);
    //            printf("\thex_n1: ");
    //            scanf("%d", &hex2);
    
    //            while(input != '\n' && getchar() != '\n' ){ /* Do Nothing to clear '\n' from a char */ }
    //            printf("%s", prompt);
    //            scanf("%c", &input);
    //            break;
    
    //            default:
    //            instruction_cycle(&cpu);
    //            // printf("Unknown Cmd, ignored \n");
    //            printf("%s", prompt);
    //            scanf("%c", &input);
    
    //            break;
    
	// 	}
    
    
	// }
	// while (input!= 'q');
    
	// printf("Halting\n");
    
    
    
    
    printf("\nRegisters:\n");
    dump_registers(&cpu);
    
    printf("\nMemory:\n");
    dump_memory(&cpu,orig,end,1);
    
    
    
    
	// /* *** STUB *** */
	// return 0;
    
    
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
    
	cpu->condition_code = 0;   // Z condition code on power-up
	cpu->running = 1;                // instruction cycle is running
    
	int regNbr =0;
	while (regNbr < NBR_REGS)
	{
        set_register(cpu, regNbr++, 0);
        
    }
    // printf("Finish Reg...\n");
    unsigned int addr = 0;
    while(addr<MEMLEN) {
        cpu->memory[addr] = 0;
        addr++;
        
    }
    
}

Word get_register(CPU *cpu, int regNbr)
{
    return cpu->reg[regNbr];
}


void set_register(CPU *cpu, int regNbr, Word newValue)
{
    
	cpu->reg[regNbr] = newValue;
    
}

Word get_memory(CPU *cpu, Address addr)
{
    return cpu->memory[addr];
}

void set_memory(CPU *cpu, Address addr, Word value)
{
    cpu->memory[addr] = value;
}


char get_condition_code(CPU *cpu)
{
    return cpu->condition_code;
}

void set_condition_code(CPU *cpu, Word value)
{
	int condition_number=0;
    condition_number = value;
    Word condition = 0;
    
    
    if(value>0){
        condition =1;
    }
    if(value==0){
        condition = condition|2;
    }
    if(value<0){
        condition = condition|4;
    }
	cpu->condition_code = condition;
}

// -------------------- INSTRUCTION ROUTINES --------------------

// Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu) {
	cpu->instr_reg = cpu->memory[cpu->pgm_counter];
	cpu->pgm_counter = (cpu->pgm_counter + 1) % MEMLEN; 		// unsigned overflow will wraparound to 0
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
	printf("%i\n",op(cpu->instr_reg));
	switch (op(cpu->instr_reg)) {
		case  0: instr_BR(cpu);   break;
        case  1: instr_ADD(cpu);   break;
        case  2: instr_LD(cpu);   break;
        case  3: instr_ST(cpu);   break;
        case  4: instr_JSR(cpu);   break;
        case  5: instr_AND(cpu);   break;
        case  6: instr_LDR(cpu);   break;
        case  7: instr_STR(cpu);   break;
        case  8: instr_RTI(cpu);   break;
        case  9: instr_NOT(cpu);   break;
        case  10: instr_LDI(cpu);   break;
        case  11: instr_STI(cpu);   break;
        case  12: instr_RTI(cpu);   break;
        case  13: instr_STI(cpu);   break;
        case  14: instr_LEA(cpu);   break;
        case  15: instr_TRAP(cpu);   break;
            /* *** STUB *** */
            
        default:
            printf("Bad opcode: %d; quitting\n", op(cpu->instr_reg));
            cpu->running = 0;
            break;
	}
}

// Execute branch instruction: Bitwise AND instruction's mask and
// cpu's condition code, branch iff result is nonzero.
//
// Echo kind of branch, current cc, whether or not the branch happened,
// and if so, the target of the branch.
//
void instr_BR(CPU *cpu) {
	int mask = bitshift(cpu->instr_reg,11,9,0);
    char maskcode[30];
    switch(mask){
        case 0 :
            strcpy(maskcode,"NOP");
            
            break;
        case 1 :
            strcpy(maskcode,"NOP");
            
            break;
        case 2 :
            strcpy(maskcode,"Z '=0'");
            
            break;
        case 3 :
            strcpy(maskcode,"PZ '>=0'");
            
            break;
        case 4 :
            strcpy(maskcode,"N '<0'");
            
            break;
        case 5 :
            strcpy(maskcode,"NP '!=0'");
            
            break;
        case 6 :
            strcpy(maskcode,"NZ '<=0'");
            
            break;
        case 7 :
            strcpy(maskcode,"BR 'unconditional'");
            
            break;
    }
    int pcoffset = bitshift(cpu->instr_reg,8,0,1);
    if(mask&get_condition_code(cpu)!=0){
        int oldcounter = cpu->pgm_counter;
        cpu->pgm_counter += pcoffset;
        
    }else{
        
    }
}
void instr_ADD (CPU *cpu)
{
	int type = bitshift(cpu->instr_reg,5,5,0);
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int src1 = bitshift(cpu->instr_reg,8,6,0);
    if(type==0){
        int src2 = bitshift(cpu->instr_reg,2,0,0);
        cpu->reg[dst] = cpu->reg[src1]+cpu->reg[src2];
        printf("ADD  R%d R%d 0 R%d;reg[%d] = %x+%x = %x\n",dst,src1,src2,dst,cpu->reg[src1],cpu->reg[src2],cpu->reg[src1]+cpu->reg[src2]);
    }else{
        int imm5 =bitshift(cpu->instr_reg,4,0,1);
        cpu->reg[dst] = cpu->reg[src1]+imm5;
        printf("ADD R%d R%d 1 %d; reg[%d] = %x +%x\n",dst,src1,imm5,dst,cpu->reg[src1],imm5,cpu->reg[src1]+imm5);
    }
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_AND (CPU *cpu)
{
	int type = bitshift(cpu->instr_reg,5,5,0);
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int src1 = bitshift(cpu->instr_reg,8,6,0);
    if(type==1){
        int src2 = bitshift(cpu->instr_reg,2,0,0);
        cpu->reg[dst] = cpu->reg[src1]&cpu->reg[src2];
        printf("AND R%d R%d 0 R%d; reg[%x]<-reg[%x]&&reg[%x] = %x\n",dst,src1,src2,dst,src1,src2,cpu->reg[src1]&cpu->reg[src2]);
    }else{
        int imm5 =bitshift(cpu->instr_reg,4,0,0);
        cpu->reg[dst] = cpu->reg[src1]&imm5;
        printf("AND R%d R%d 1 %x;  reg[%x]<-reg[%x]&&%x = %x\n",dst,src1,imm5,dst,src1,imm5,cpu->reg[src1]&imm5);
    }
    set_condition_code(cpu,cpu->reg[dst]);
}

void instr_err (CPU *cpu)
{
	printf("ERROR\n");
}
void instr_JMP (CPU *cpu)
{
	int base = bitshift(cpu->instr_reg,8,6,0);
    cpu->pgm_counter = cpu->reg[base];
    printf("JMP New pgm_counter = reg[%d] = %x\n",base,cpu->reg[base]);
    
}
void instr_JSR (CPU *cpu)
{
	printf("JSR\n");
}

//functions that i suppose they are right
void instr_LD  (CPU *cpu)        {
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int pcoffset = bitshift(cpu->instr_reg,8,0,1);
    cpu->reg[dst] = cpu->memory[cpu->pgm_counter+pcoffset];
    printf("LD R%d %d ; reg[%x]<- memory[%x] = %x ,\n",dst,pcoffset,dst,cpu->pgm_counter+pcoffset,cpu->memory[cpu->pgm_counter+pcoffset]);
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_LDI (CPU *cpu)        {
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int pcoffset = (int)bitshift(cpu->instr_reg,8,0,1);
    cpu->reg[dst] = cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]];
    printf("LDI R%d %x %x ; reg[%x] <- memory[memory[%x+%x]] = %x \n",dst,pcoffset,cpu->pgm_counter,dst,pcoffset,cpu->pgm_counter,cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]]);
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_LDR (CPU *cpu)        {
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int base = bitshift(cpu->instr_reg,8,6,0);
    int offset = (int)bitshift(cpu->instr_reg,5,0,1);
    cpu->reg[dst] = cpu->memory[cpu->reg[base]+offset];
    printf("LDR R%d %x %x ; reg[%x] <-memory[reg[%x]+%x] = %x\n",dst,base,offset,dst,base,offset,cpu->memory[cpu->reg[base]+offset]);
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_LEA (CPU *cpu)        {
    int dst = bitshift(cpu->instr_reg,11,9,0);
    int pcoffset = (int)bitshift(cpu->instr_reg,8,0,1);
    cpu->reg[dst] = cpu->pgm_counter+pcoffset;
    printf("LEA R%d %x %x ; Reg[%x] <- %x + %x = %x \n",dst,cpu->pgm_counter,pcoffset,dst,cpu->pgm_counter,pcoffset,cpu->pgm_counter+pcoffset);
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_NOT (CPU *cpu)
{
	int dst = bitshift(cpu->instr_reg,11,9,0);
    int src = bitshift(cpu->instr_reg,8,6,0);
    cpu->reg[dst] = ~cpu->reg[src];
    printf("NOT R%d R%d ; reg[%x]<-~reg[%x] = \n",dst,src,dst,src,~cpu->reg[src]);
    set_condition_code(cpu,cpu->reg[dst]);
}
void instr_RTI (CPU *cpu)
{
	printf("RTI\n");
}
void instr_ST  (CPU *cpu)
{
	int src = bitshift(cpu->instr_reg,11,9,0);
    int pcoffset = bitshift(cpu->instr_reg,8,0,1);
    cpu->memory[cpu->pgm_counter+pcoffset] = cpu->reg[src];
    printf("ST R%d %x %x ; memory[%x] <-reg[%x] = %x,\n",src,cpu->pgm_counter,pcoffset,src,cpu->pgm_counter+pcoffset,cpu->reg[src]);
}
void instr_STI (CPU *cpu)

{
    int src = bitshift(cpu->instr_reg,11,9,0);
    int pcoffset = bitshift(cpu->instr_reg,8,0,1);
    cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]] = cpu->reg[src];
    printf("STI R%d %x ; memory[memory[%x+%x]]<-reg[%x] = %x \n",src,pcoffset,cpu->pgm_counter,pcoffset,src,cpu->reg[src]);
}

void instr_STR (CPU *cpu)
{
	int dst = bitshift(cpu->instr_reg,11,9,0);
    int base = bitshift(cpu->instr_reg,8,6,0);
    int offset = bitshift(cpu->instr_reg,5,0,1);
    cpu->memory[base+offset] = cpu->reg[dst];
    printf("STR R%d R%d %x ; memory[%x+%x] = reg[%x]= %x\n",dst,base,offset,offset,cpu->pgm_counter,dst,cpu->reg[dst]);
}
void instr_TRAP(CPU *cpu)
{
    int vectors = bitshift(cpu->instr_reg,7,0,0);
    Word pointer;
    char temp;
    switch(vectors){
        case 32:
            printf("input a char:");
            scanf("%c",&temp);
            cpu->reg[0] = cpu->reg[0]&0;
            cpu->reg[0] =temp;
            printf("read a char '%c'\n",temp);
            break;
        case 33:
            temp = cpu->reg[0];
            printf("%c",temp);
            break;
        case 34:
            
            pointer = cpu->reg[0];
            while(cpu->memory[pointer]){
                printf("%c",cpu->memory[pointer]);
                pointer++;
            }
            break;
        case 35:
            printf("Input a char:");
            scanf("%c",&temp);
            cpu->reg[0] = cpu->reg[0]&0;
            cpu->reg[0] =temp;
            printf("read a char '%c'\n",temp);
            break;
        case 37:
            cpu->running = 0;
            break;
    }
    printf("\n");
}


void dump_control_unit(CPU *cpu)
{
	dump_registers(cpu);
}
//
/* *** STUB *** */
Word op(Word w)
{
    Word op = w>>12;
    return op;
}

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
    if(nonzero_only==1){
        Address i;
        for(i=from;i<=to;i++){
            if(cpu->memory[i]!=0){
                printf("  x%04hX: x%04hX\n", i, cpu->memory[i]);
            }
        }
    }else{
        Address i ;
        for(i=from;i<=to;i++){
            printf("  x%04hX: x%04hX\n", i, cpu->memory[i]);
        }
    }
}


void dump_registers(CPU *cpu)
{
    printf("PC = x%04d   IR = x%04d   CC = Z\n", cpu->reg[0], cpu->instr_reg);
    
	Address i, j;
	int loc = 0;
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


//
int bitshift(Word content,int left,int right,int needsign){
    int mask = (1<<left+1)-1;
    int result = content&mask;
    result = result >>right;
    if(needsign==1){
        if(result&(1<<(right-left))!=0){
            result=result-power2(left-right+1);
            printf("negative number!");
        }
    }
    return result;
}


int power2(int point){
    int i;
    long result = 1;
    for(i =0;i<point;i++){
        result = result*2;
    }
    return result;
}
