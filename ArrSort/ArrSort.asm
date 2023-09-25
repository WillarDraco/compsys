// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

@R1
D = M - 1
@R2
D = M + D
@last
M = D

// Check array length if 0 end
@R2
D = M
@END
D;JLE


(OUTER)
	@R1
	D = M
	@last
	D = D - M
	@END
	D;JGT

	@R1
	D = M
	@R3
	M = D + 1

(INNER)
	@R3
	D = M
	@last
	D = D - M
	@INNERFIN
	D;JGT
	
	@R3 //inner index
	A = M
	D = M //dereferenced value
	@look // Look at value
	M = D
	@ELEM_POS
	M;JGE
	@ELEM_NEG
	0;JMP

//Swaps elements
(SWAP)
	@compare
	D = M
	@temp
	M = D
	@look
	D = M
	@R1
	A = M
	M = D

	@temp
	D = M
	@R3
	A = M
	M = D

//Iterate the loop
(INLOOP)
	@R3
	M = M + 1
	@INNER
	0;JMP

(INNERFIN)
	@R1
	M = M + 1
	@OUTER
	0;JMP

(DOUBLE)
	@look
	D = M
	@compare
	D = D - M
	@INLOOP
	D;JGE
	@SWAP
	0;JMP

(ELEM_NEG)
	@R1
	A = M
	D = M
	@compare // Check value
	M = D
	@DOUBLE
	M;JLT
	@SWAP
	0;JMP

(ELEM_POS)
	@R1
	A = M
	D = M
	@compare // Check value
	M = D
	@DOUBLE
	M;JGE
	@INLOOP
	0;JMP

(END)
	@R0
	M = -1
	@END
	0;JMP