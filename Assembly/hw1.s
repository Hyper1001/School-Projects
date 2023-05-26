.global add32 @done
.global sub64 @done
.global minU16
.global minS16
.global isLessThanU16
.global isLessThanS16
.global shiftLeftU16
.global shiftU32
.global shiftS8
.global isEqualU32 @done
.global isEqualS8 @done

.text

add32:
	ADD R0, R0, R1
	BX LR
sub64:
	SUBS R0, R0, R2
	ADC R1, R1, R3
	BX LR

minU16:
	CMP R0, R1
	BLE minU16end
	MOV R0, R1

minU16end:
	BX LR

minS16:
	CMP R0, R1
	BLE minS16end
	MOV R0, R1

minS16end:
	BX LR

isLessThanU16:
	CMP R0, R1
	MOV R0, #0
	BGE isntLessThanU16
	MOV R0, #1

isntLessThanU16:
	BX LR

isLessThanS16:
	CMP R0, R1
	MOV R0, #0
	BGE isntLessThanS16
	MOV R0, #1

isntLessThanS16:
	BX LR

shiftLeftU16:

shiftU32:

shiftS8:

isEqualU32:
	CMP R0, R1
	MOV R0, #0
	BNE isntEqualU32
	MOV R0 , #1 

isntEqualU32:
	BX LR

isEqualS8:
	CMP R0, R1
	MOV R0, #0
	BNE isntEqualS8
	MOV R0 , #1 

isntEqualS8:
	BX LR