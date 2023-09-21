// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

@R0
M = 0

@R4
M = 0

@R1  // 0 Check
D = M
@END
D;JEQ

@R2  // 0 Check
D = M
@END
D;JEQ

// Negative Check
@R1
D = M
@NEGX
D;JLT

// Negative Check
(CHECK)
@R2
D = M
@NEGY
D;JLT

@INIT
0;JMP

//Creating non negative number
(NEGX)
@R4
M = M + 1

@R1
M = -M
@CHECK
0;JMP

//Creating non negative number
(NEGY)
@R4
M = M + 1

@R2
M = -M
@INIT
0;JMP


// Loop Init
(INIT)
@R1  
D = M
@R3
M = D

// Addition loop
(MULT)
@R2
D = M

@R0
M = D + M

@R3
M = M - 1
D = M
@MULT
D;JGT

(NEGDEAL)
@R4
D = M
@END
D;JLE

@R0
M = -M

@R4
M = M - 1
@NEGDEAL
0;JMP

(END)
@END
0;JMP