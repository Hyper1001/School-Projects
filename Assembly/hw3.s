.global sortDecendingInPlace
.global sumF32
.global prodF64
.global dotpF64
.global maxF32
.global absSumF64
.global sqrtSumF64
.global getDirection
.global getAddNo
.global getCity

.text

sortDecendingInPlace:
	@not attempted

sumF32:
	MOV R2, #0
	VMOV S0, R2, R2 @Zero out accumlator. S register

sumF32_loop:
	CMP R1, #0
	BEQ sumF32_end
	VLDR.F32 S1,[R0] @Load float in [R0] to S1
	VADD.F32 S0,S0,S1 @Add S1 to accumlator
	SUB R1, R1, #1 @Decrement counter
	ADD R0,R0, #4 @Move address forowards 32-bits

sumF32_end:
	VMOV R0, R1, S0
	BX LR
	
prodF64:
	VMOV S4, R1 @ Save count in scalar, we'll need it later
	MOV R2, #0
	VMOV D0, R2, R2 @ Zero out accumulator

prodF64_loop:
	CMP R1, #0 @ Check counter
	BEQ prodF64_end

	VLDR.F64 D1, [R0]	@ Load double in [R0] to D1
	VMUL.F64 D0, D0, D1 @ Add D1 to accumulator

	SUB R1, R1, #1 @ Decrement counter
	ADD R0, R0, #8 @ Move address forward 64-bits
	B prodF64_loop

prodF64_end:
	VCVT.F64.U32 D1, S4 @ Convert uint32_t to double, save in D1
	VMOV R0, R1, D0
	BX LR

dotpF64:
	MOV R3, #0
	VMOV D0, R3, R3 @ Zero out accumulator
	MOV R4, R2 @ second counter
	MOV R5, R2 @ placeholder counter to be copied, since 2 counters will be altered.

dotpF64_loop:
	CMP R1, #0 @Check counter
	BEQ dotpF64_end
	B dotpF64_loop1

dotpF64_loop1:
	CMP R4, #0 @ Check counter
	BEQ dotpF64_loop2
	VLDR.F64 D1, [R0] @ First Array
	VLDR.F64 D2, [R1] @ Second Array
	VMUL.F64 D1, D1, D2 @ Multiply them
	VADD.F64 D0,D0,D1 @ Add to final answer
	SUB R4,R4,#1 @ Decrement counter
	ADD R1,R1,#8 @ Move R1 forward
	B dotpF64_loop1

dotpF64_loop2:
	SUB R2,R2,1 @ Decrement counter
	ADD R0,R0,#8 @ Move R0 forward
	MOV R4, R5 @Reset counter
	B dotpF64_loop

dotpF64_end:
	VMOV R0, R2, D0
	BX LR
	
maxF32:
	MOV R2, #0
	VMOV S0, R2, R2 @Zero out accumaltor.

maxF32_loop:
	CMP R1, #0 @ Done with count?
	BEQ maxF32_end @ end if done with count
	VLDR.F32 S1,[R0] @ loads float in [R0] to S1.
	VCMP.F32 S0,S1 @ Compare S0 (initially 0) and S1
	SUB R1, R1, #1 @ Decrement counter
	ADD R0,R0,#4 @ Move forwards 32-bits
	BLE maxF32_loop @ restart loop if less or equal, continue with loop if greater
	VMOV.F32 S0, S1 @ Move S1 to S0 b/c S1 is greater.
	B maxF32_loop @ Go through loop again

maxF32_end:
	VMOV R0,R1,S0
	BX LR	
	
absSumF64:
	VMOV S4, R1 @ Save count in scalar, we'll need it later
	MOV R2, #0
	VMOV D0, R2, R2 @ Zero out accumulator

absSumF64_loop:
	CMP R1, #0 @ Check counter
	BEQ absSumF64_end

	VLDR.F64 D1, [R0]	@ Load double in [R0] to D1
	VADD.F64 D0, D0, D1 @ Add D1 to accumulator

	SUB R1, R1, #1 @ Decrement counter
	ADD R0, R0, #8 @ Move address forward 64-bits
	B absSumF64_loop

absSumF64_end:
	VCVT.F64.U32 D1, S4 @ Convert uint32_t to double, save in D1
	VABS.F64 D0, D1 @Convert sum to its absolute value and store it in D0
	VMOV R0, R1, D0
	BX LR

sqrtSumF64:
	MOV R2, #0
	VMOV D0, R2, R2 @ Zero out accumulator	

sqrtSumF64_loop:
	CMP R1, #0 @check counter
	BEQ sqrtSumF64_end
	VLDR.F64 D1, [R0] @load double in R0 to D1
	VADD.F64 D0, D0, D1 @Add D1 to accumaltor
	SUB R1, R1, #1 @Decrement counter
	ADD R0, R0, #8
	B sqrtSumF64_loop

sqrtSumF64_end:
	VSQRT D0, D0 @Square roots and stores in the same register
	VMOV R0, R1, D0
	BX LR
	
getDirection:
	SUB R1, R1, #1 @ subtract so index is consistent, according to driver
	MOV R3, #120 @ size of one business
	MUL R2, R1,R3 @ multiply
	ADD R0, R0, #44 @ Offset of direction
	ADD R0, R0, R2 @ add offset + array position
	BX LR

getAddNo:
	SUB R1, R1, #1 @ subtract so index is consistent, according to driver
	MOV R3, #120 @ size of one business
	MUL R2, R1,R3 @ multiply
	ADD R0, R0, #40 @ Offset of Address Number 
	ADD R0, R0, R2 @ add offset + array position
	LDR R0, [R0]
	BX LR

getCity:
	SUB R1, R1, #1 @ subtract so index is consistent, according to driver
	MOV R3, #120 @ size of one business
	MUL R2, R1,R3 @ multiply
	ADD R0, R0, #78 @ offset of city
	ADD R0, R0, R2 @ add offset + array position
	BX LR