# CDA3103
Programming project (HW4)

Authors: Jeremiah Registre, Daniel Palencia

This program multiplies two numbers (2x3) using a virtual tiny machine.
It uses elf.txt to provide input for the program
It prints the output into output.txt

NOTE: Be sure to have tinyvm.c and elf.txt in the same folder when running. You must also be currently located in that folder when running. You do not have to already have output.txt in the folder, nor must it exist before running since it will be overwritten/created when the program is ran.

In order to run:
Compile using 'gcc tinyvm.c -o tinyvm'
Run with '.\tinyvm elf.txt'
When prompted, enter the appropriate numbers
NOTE: The first two numbers to be inputted can be whatever two positive, nonzero numbers of your choosing. These two are the numbers to be multiplied. There will be a third prompt for input, you MUST enter '1', otherwise the program will not properly multiply the numbers.
Output will be printed into output.txt

NOTE: output.txt will get erased and replaced every time the program is ran.