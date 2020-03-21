	AREA ARMex, CODE, READONLY
		ENTRY

Start
	MOV r0,#1 		  ;store 1 in r0
	MOV r0,r0,LSL #1  ;r0= r0*2 = 1*2 = 2
	MOV r0,r0, LSL #1 ;r0= r0*2 = 2*2 = 4
	MOV r0,r0, LSL #1 ;r0= r0*2 = 4*2 = 8
	
	MOV r1,#1		  ;store 1 in r1
	MOV r1,r1, LSL #1 ;r1= r1*2 = 1*2 = 2
	
	MOV r2,#1 		 ;store 1 in r2
	
	ADD r3,r0,r1 	 ; r3=r0+r1
	ADD r3,r3,r2 	 ; r3=r3+r2
	
	MOV r4,r3		 ;r4=r3
	
	MOV r6,#1 		 ;store 1 in r6
	MOV r6,r6,LSL #1 ;r6= r6*2 = 1*2 = 2
	MOV r6,r6,LSL #1 ;r6= r6*2 = 2*2 = 4
	MOV r6,r6, LSL #1 ;r6= r6*2 = 4*2 = 8
	
	MOV r7,#1		 ;store 1 in r7
	MOV r7,r7, LSL #1 ;r7= r7*2 = 1*2 = 2
	
	ADD r8,r6,r7	 ;r8= r6+r7 = 8+2= 10
	
	MOV r9,#1		 ;store 1 in r9

Loop
	ADD r3,r3,r1	 ;r3= r3+2
	ADD r4,r4,r3 	 ;r4= r4+r3
	ADD r9,r9,#1 	 ;r9=r9+1
	
	CMP r9,r8		 ;compare r9 with r8
	BEQ EndLine
	B Loop
	
	
	
EndLine
	LDR r0, Address1      ;load Address1 in r0
	STR r4, [r0]          ;store r4 in r0
	MOV pc, lr

Address1 & &4000