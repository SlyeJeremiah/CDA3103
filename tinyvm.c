#include <stdio.h>

// Instruction Memory (IM)
int IM[128] = {0};

// Data Memory (DM)
int DM[10] = {0};

// Registers
int PC = 0; // Program Counter
int A = 0; // Accumulator
int MAR = 0; // Memory Address
int MDR = 0; // Memory Data
typedef struct { 
    int op; // OP code
    int addr; // address
} InstructionRegister; // Instruction Register

InstructionRegister IR;

int main(int argc, char **file) {
    int EOP = 1;
    FILE *InputFile = fopen(file[1], "r"); //Open input file passed in from command line
    FILE *OutFile = fopen("output.txt", "w"); //Open output file hard coded

    // Load instructions into IM (instruction memory array)
    int opcode, operand;
    int index = 0;
    while (fscanf(InputFile, "%d %d", &opcode, &operand) == 2 && index < 128) {
        // good to note that the "== 2" makes sure that the number of successfully read integers from a line is 2
        IM[index] = opcode;
        index++;
        IM[index] = operand;
        index++;
    }

    while ( EOP == 1 ) {

        // FETCH
        IR.op = IM[PC];
        IR.addr = IM[PC + 1];
        PC = PC + 2;

        // EXECUTE
        switch (IR.op)
        {
            case 1:
                // LOAD <addr>
                MAR = IR.addr;
                MDR = DM[MAR];
                A = MDR;
                break;
    
            case 2: 
                // ADD
                MAR = IR.addr;
                MDR = DM[MAR];
                A = A + MDR;
                break;

            case 3:
                // STORE
                MAR = IR.addr;
                MDR = A;
                DM[MAR] = MDR;
                break;

            case 4:
                // SUB
                MAR = IR.addr;
                MDR = DM[MAR];
                A = A - MDR;
                break;

            case 5:
                // IN <5>
                scanf("%d", &A);
                break;

            case 6:
                // OUT <7>
                printf("%d", A);
                break;

            case 7:
                // HALT
                EOP = 0;
                break;
    
            case 8:
                // JMP <addr>
                PC = IR.addr;
                break;

            case 9:
                // SKIPZ
                if ( A == 0 ) {
                    PC = PC + 4;
                }
                break;

            case 10:
                // SKIPG
                if ( A > 0 ) {
                    PC = PC + 4;
                }
                break;

            case 11:
                // SKIPL
                if ( A < 0 ) {
                    PC = PC + 4;
                }
                break;
        }
        // Print current state of PC, AC, DM after each instruction
        fprintf(OutFile, "PC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]", PC, A, DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);
    }
    //Close all files
    fclose(InputFile);
    fclose(OutFile);

    return 0;
}