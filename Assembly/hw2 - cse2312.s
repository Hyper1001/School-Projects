.global stringCopy
.global stringCat
.global sumS32
.global sumS16
.global sumU32_64
.global countNegative
.global countNonNegative
.global countMatches
.global returnMax
.global returnMin
.text

stringCopy:
	MOV R3, #1 @counter

stringCopyLoop:
	LDRB R1, [R3], #1 @load and store byte by byte
	STRB R0, [R3], #1
	ADD R3, #1
	CMP R0, #0
	ADD R3, #1
	BNE stringCopyLoop
	BX LR 

stringCat:
	MOV R2, R0

stringCatLoop1:
	LDRB R2, [R3], #1
    	CMP R2, #0
    	BNE stringCatLoop1   
    	SUB R3, R3, #1

stringCatLoop2:
	LDRB R2, [R1], #1
   	STRB R2, [R3], #1 
    	CMP R2, #0
    	BNE stringCatLoop2
	BX LR	
	
sumS32:
	MOV R2, R0
	MOV R0, #0

sumS32_loop:
	LDRH R3, [R2], #2
	ADD R0, R0, R3
	SUBS R1, R1, #1
	BNE sumS32_loop
	BX LR

sumS16:
	MOV R2, R0
	MOV R0, #0

sumS16_loop:
	LDRH R3, [R2], #2
	ADD R0, R0, R3
	SUBS R1, R1, #1
	BNE sum16_loop
	BX LR

sumU32_64:
	MOV R2, R0
	MOV R0, #0

sumU32_64_loop:
	LDRH R3, [R2], #2
	ADD R0, R0, R3
	SUBS R1, R1, #1
	BNE sumU32_64_loop
	BX LR

countNonNegative:
	MOV R2, R0
	MOV R0, #0

countNonNegative_loop:
	LDRH R3, [R2], #2
	CMP R3, #0
	BMI countNonNegative_branch
	ADD R0, #1
	SUBS R1, R1, #1
	BNE countNonNegative_loop
	BX LR

countNonNegative_branch:
	SUBS R1, R1, #1
	BNE countNonNegative_loop
	BX LR

countNonNegative:
	MOV R2, R0
	MOV R0, #0

countNonNegative_loop:
	LDRH R3, [R2], #2
	CMP R3, #0
	BMI countNonNegative_branch
	ADD R0, #1
	SUBS R1, R1, #1
	BNE countNonNegative_loop
	BX LR

countNonNegative_branch:
	SUBS R1, R1, #1
	BNE countNonNegative_loop
	BX LR

countMatches_loop:
	LDRB R3, [R2], #1
	CMP R3, R1
	BEQ countMatches_branch
	CMP R3, #0
	BNE countMatches_loop
	BEQ countMatches_end

countMatches_branch:
	ADD R0, #1 
	CMP R3, #0

countMatches_end:
	CMP R0, #0
	BEQ countMatches_end1
	BX LR

returnMax:
	MOV R2, R0
	MOV R0, #0
	SUB R0, #2147483647

returnMax_loop:
	LDRH R3, [R2], #2
	CMP R3, R0
	BLE returnMax_branch
	MOV R0, R3
	SUBS R1, R1, #1
	BNE returnMax_loop
	BX LR

returnMax_branch:
	SUBS R1, R1, #1
	BNE returnMax_loop
	BX LR

returnMin:
	MOV R2, R0
	MOV R0, #2147483647

returnMin_loop:
	LDRH R3, [R2], #2
	CMP R3, R0
	BGE returnMin_branch
	MOV R0, R3
	SUBS R1, R1, #1
	BNE returnMin_loop
	BX LR

returnMin_branch:
	SUBS R1, R1, #1
	BNE returnMin_loop
	BX LR