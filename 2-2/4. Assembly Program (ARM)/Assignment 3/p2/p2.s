	AREA ARMex, CODE, READONLY
		ENTRY
		
Start
	LDR r10, Address1			;load Address1 to r10
	
	MOV r1, #1  ;r0 = 1
	MOV r2, #2	;r1 = 2
	MOV r3, #3	;r2 = 3
	MOV r4, #4	;r3 = 4
	MOV r5, #5	;r4 = 5
	MOV r6, #6	;r5 = 6
	MOV r7, #7	;r6 = 7
	MOV r8, #8	;r7 = 8
	MOV r9, #9	;r8 = 9
	MOV r0, #10	;r9 = 10
	
	STR r1, [r10], #4	;store r1 in r10, r10=r10+4byte :1
	
	STR r2, [r10], #4	;store r2 in r10, r10=r10+4byte :1*2
	
	MUL r1, r2, r3		;r1=r2*r3						=1*2*3 
	STR r1, [r10], #4	;store r1 in r10, r10=r10+4byte
	
	MUL r2, r1, r4		;r2=r1*r4						=1*2*3*4
	STR r2, [r10], #4	;store r2 in r10, r10=r10+4byte
	
	MUL r3, r2, r5		;r3=r2*r5						=1*2*3*4*5 
	STR r3, [r10], #4	;store r3 in r10, r10=r10+4byte
	
	MUL r4, r3, r6		;r4=r3*r6						=1*2*3*4*5*6 
	STR r4, [r10], #4	;store r4 in r10, r10=r10+4byte
	
	MUL r5, r4, r7		;r5=r4*r7						=1*2*3*4*5*6*7 
	STR r5, [r10], #4	;store r5 in r10, r10=r10+4byte
	
	MUL r6, r5, r8		;r6=r5*r8						=1*2*3*4*5*6*7*8
	STR r6, [r10], #4	;store r6 in r10, r10=r10+4byte
	 
	MUL r7, r6, r9		;r7=r6*r9						=1*2*3*4*5*6*7*8*9 
	STR r7, [r10], #4	;store r7 in r10, r10=r10+4byte
	
	MUL r8, r7, r0		;r8=r7*r00						=1*2*3*4*5*6*7*8*9*10
	STR r8, [r10], #4	;store r8 in r10, r10=r10+4byte
	
	MOV pc, lr			;pc=lr
		
Address1 & &00040000	;Address1=40000
	end