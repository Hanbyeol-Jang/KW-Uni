	AREA ARMex, CODE, READONLY
		ENTRY
	
start
	LDR r0, =Array1		;store Array1 in r0
	LDR r1, Address1	;store Address1 in r1
	MOV r3,#10			;r3=10
	
Loop
	LDR r8,[r0],#4			; load r0 to r8, r0=r0+4
	STRB r8,[r1],#-1		; store r8 in r1, r1=r1-1
	ADD r4,r4,#1 			; r4=r4+1
	CMP r4,r3				; compare r4 with r3
	BEQ Endline
	B Loop
	
Endline
	MOV pc,lr

Array1 DCD 10,9,8,7,6,5,4,3,2,1

Address1 & &00004009		; start storing address from 4009 to 4000