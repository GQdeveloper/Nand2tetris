// Assigning values to compute in to the ram
@3
D=A
@R0
M=D
@4
D=A
@R1
M=D
//Counter
@R1
D=M
@R3
M=D
// Loop that computes de multiplication
(LOOP)
@R0
D=M
@R2
M=D+M
@R3
M=M-1
D=M
@LOOP
D;JGT