	AREA ARMex, CODE, READONLY
		ENTRY
start

	MOV r0,#1 		  ;store 1 in r0
	MOV r0,r0,LSL #1  ;r0= r0*2 = 1*2 = 2
	MOV r0,r0, LSL #1 ;r0= r0*2 = 2*2 = 4
	MOV r0,r0, LSL #1 ;r0= r0*2 = 4*2 = 8
	
	MOV r1,#1		  ;store 1 in r1
	MOV r1,r1, LSL #1 ;r1= r1*2 = 1*2 = 2
	
	ADD r2,r0,r1      ;r2=r0+r1=8+2=10
	ADD r3,r2,r2      ;r3=r2+r2=10+10=20
	
	MUL r4,r3,r2      ;r4=r3*r2
	
	LDR r5, Address1  ;load Address1 in r5
	
	STR r4,[r5]		  ; store r4 in r5
	
	MOV pc, lr
	
Address1 & &4000
	END