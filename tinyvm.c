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

int main() {
    int EOP = 1;

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
        }
    }
    
    return 0;
}