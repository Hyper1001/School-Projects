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
	MOV R2, #0
	VMOV D0, R2, R2
	VMOV R0, R1, D0 

sumF32:
	MOV R2, #0
	VMOV S0, R2

sumF32_loop:
	CMP R1, #0
	BEQ sumF32_end
	VLDR.F32 S1,[R0]
	VADD.F32 S0,S0,S1
	SUB R1, R1, #1
	ADD R0,R0, #4
	B sumF32_loop

sumF32_end:
	VMOV R0, S0
	BX LR
	
prodF64:
	VMOV S4, R1
	MOV R2, #0
	VMOV D0, R2, R2
	VLDR.F64 D1, [R0]
	VADD.F64 D0, D0, D1
	ADD R0, R0,#8
	SUB R1, R1, #1

prodF64_loop:
	CMP R1, #0
	BEQ prodF64_end

	VLDR.F64 D1, [R0]
	VMUL.F64 D0, D0, D1

	SUB R1, R1, #1
	ADD R0, R0, #8
	B prodF64_loop

prodF64_end:
	VCVT.F64.U32 D1, S4
	VMOV R0, R1, D0
	BX LR

dotpF64:
	MOV R3, #0
	VMOV D0, R3, R3

dotpF64_loop:
	CMP R2, #0
	BEQ dotpF64_end
	VLDR.F64 D1, [R0]
	VLDR.F64 D2, [R1]
	VMUL.F64 D1, D1, D2
	VADD.F64 D0, D0, D1
	SUB R2, R2, #1
	ADD R0, R0, #8
	ADD R1, R1, #8
	B dotpF64_loop

dotpF64_end:
	VMOV R0, R1, D0
	BX LR
	
maxF32:
	MOV R2, #0

maxF32_loop:
	CMP R1, #0
	BEQ maxF32_end
	VLDR.F32 S1,[R0]
	VCMP.F32 S0,S1
	SUB R1, R1, #1
	ADD R0,R0,#4
	BLE maxF32_loop
	VMOV.F32 S0, S1
	B maxF32_loop

maxF32_end:
	VMOV R0, S0
	BX LR	
	
absSumF64:
	VMOV S4, R1
	MOV R2, #0
	VMOV D0, R2, R2

absSumF64_loop:
	CMP R1, #0
	BEQ absSumF64_end

	VLDR.F64 D1, [R0]
	VADD.F64 D0, D0, D1

	SUB R1, R1, #1
	ADD R0, R0, #8 
	B absSumF64_loop

absSumF64_end:
	VABS.F64 D0, D0
	VMOV R0, R1, D0
	BX LR

sqrtSumF64:
	MOV R2, #0
	VMOV D0, R2, R2

sqrtSumF64_loop:
	CMP R1, #0
	BEQ sqrtSumF64_end
	VLDR.F64 D1, [R0]
	VADD.F64 D0, D0, D1
	SUB R1, R1, #1
	ADD R0, R0, #8
	B sqrtSumF64_loop

sqrtSumF64_end:
	VSQRT.F64 D0, D0
	VMOV R0, R1, D0
	BX LR
	
getDirection:
	MOV R3, #120 
	MUL R2, R1,R3
	ADD R0, R0, #44
	ADD R0, R0, R2
	LDR R0, [R0]
	BX LR

getAddNo:
	MOV R3, #120
	MUL R2, R1,R3
	ADD R0, R0, #40
	ADD R0, R0, R2
	LDR R0, [R0]
	BX LR

getCity:
	MOV R3, #120
	MUL R2, R1,R3
	ADD R0, R0, #78
	ADD R0, R0, R2
	BX LR

