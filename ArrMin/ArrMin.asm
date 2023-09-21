// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

@R0
M = 0
@ptr
M = 0

// Check array length if 0 end
@R2
D = M
@END
D;JLE

//Puts first element as first min
@R1
A = M
D = M
@R0
M = D

//Copies pointer starting at the second element of the array
@R1
D = M
@ptr
M = D + 1

@i
M = 1

//Comparing each value loop
(MIN)
@i
D = M
@R2
D = D - M
@END
D;JEQ

@ptr
A = M
D = M
@ELEM_POS
D;JGE
@ELEM_NEG
0;JMP

//New Min
(NEWMIN)
@ptr
A = M
D = M
@R0
M = D

//Iterate the loop
(LOOP)
@i
M = M + 1
@ptr
M = M + 1
@MIN
0;JMP

(REF_NEG)
(REF_POS)
@ptr
A = M
D = M
@R0
D = D - M
@LOOP
D;JGE
@NEWMIN
0;JMP

(ELEM_NEG)
@R0
D = M
@REF_NEG
D;JLT
@LOOP
0;JMP

(ELEM_POS)
@R0
D = M
@REF_POS
D;JGE
@LOOP
0;JMP

(END)
@END
0;JMP