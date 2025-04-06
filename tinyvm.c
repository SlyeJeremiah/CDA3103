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

    printf("Initial values\n");
    fprintf(OutFile, "Initial values\n");
    printf("PC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n\n", PC, A, DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);
    fprintf(OutFile, "PC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n\n", PC, A, DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);

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
                printf("LOAD <%d>\n", IR.addr);
                fprintf(OutFile, "LOAD <%d>\n", IR.addr);

                MAR = IR.addr;
                MDR = DM[MAR];
                A = MDR;
                break;
    
            case 2: 
                // ADD
                printf("ADD <%d>\n", IR.addr); 
                fprintf(OutFile, "ADD <%d>\n", IR.addr);

                MAR = IR.addr;
                MDR = DM[MAR];
                A = A + MDR;
                break;

            case 3:
                // STORE
                printf("STORE <%d>\n", IR.addr); 
                fprintf(OutFile, "STORE <%d>\n", IR.addr);

                MAR = IR.addr;
                MDR = A;
                DM[MAR] = MDR;
                break;

            case 4:
                // SUB
                printf("SUB <%d>\n", IR.addr); 
                fprintf(OutFile, "SUB <%d>\n", IR.addr);

                MAR = IR.addr;
                MDR = DM[MAR];
                A = A - MDR;
                break;

            case 5:
                // IN <5>
                printf("IN <5>\n");
                fprintf(OutFile, "IN <5>\n");
                printf("Input a value: ");
                scanf("%d", &A);
                fprintf(OutFile, "Input a value: %d", A);
                printf("\n");
                fprintf(OutFile, "\n");
                break;

            case 6:
                // OUT <7>
                printf("OUT <7>\nResult is: %d\n", A);
                fprintf(OutFile, "OUT <7>\nResult is: %d\n", A);
                break;

            case 7:
                // HALT
                printf("HALT\n"); 
                fprintf(OutFile, "HALT\n");

                EOP = 0;
                break;
    
            case 8:
                // JMP <addr>
                printf("JMP <%d>\n", IR.addr); 
                fprintf(OutFile, "JMP <%d>\n", IR.addr);

                PC = IR.addr;
                break;

            case 9:
                // SKIPZ
                printf("SKIPZ\n"); 
                fprintf(OutFile, "SKIPZ\n");

                if ( A == 0 ) {
                    PC = PC + 2;
                }
                break;

            case 10:
                // SKIPG
                printf("SKIPG\n"); 
                fprintf(OutFile, "SKIPG\n");

                if ( A > 0 ) {
                    PC = PC + 2;
                }
                break;

            case 11:
                // SKIPL
                printf("SKIPL\n"); 
                fprintf(OutFile, "SKIPL\n");
                
                if ( A < 0 ) {
                    PC = PC + 2;
                }
                break;
        }
        // Print current state of PC, AC, DM after each instruction
        fprintf(OutFile, "\nPC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n\n", PC, A, DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);
    }

    printf("End of Program.");
    fprintf(OutFile, "End of Program.");

    //Close all files
    fclose(InputFile);
    fclose(OutFile);

    return 0;
}