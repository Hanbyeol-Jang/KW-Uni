	AREA pr2, CODE, READONLY
		ENTRY
		
Start
	MOV r0, #10		;r0=10
	MOV r1, #11		;r1=11
	MOV r2, #12		;r2=12
	MOV r3, #13		;r3=13
	MOV r4, #14		;r4=14
	MOV r5, #15		;r5=15
	MOV r6, #16		;r6=16
	MOV r7, #17		;r7=17
	
	MOV r9,#160		;r9=160
	
	LDR r12, Address1		;load Address1 to r12
	
	STMFA sp!,{r0-r7}		;store r0-r7 into stack by full ascending and update up 
	
	B doRegister			;enter into function doRegister
	
doRegister
	ADD r0, r0, #0			; r0=r0+0
	ADD r1, r1, #1			; r1=r1+1
	ADD r2, r2, #2			; r2=r2+2
	ADD r3, r3, #3			; r3=r3+3
	ADD r4, r4, #4			; r4=r4+4
	ADD r5, r5, #5			; r5=r5+5
	ADD r6, r6, #6			; r6=r6+6
	ADD r7, r7, #7			; r7=r7+7
	
	ADD r8, r0, r1			; r8=r0+r1
	ADD r8, r8, r2			; r8=r0+r1+r2
	ADD r8, r8, r3			; r8=r0+r1+r2+r3
	ADD r8, r8, r4			; r8=r0+r1+r2+r3+r4
	ADD r8, r8, r5			; r8=r0+r1+r2+r3+r4+r5
	ADD r8, r8, r6			; r8=r0+r1+r2+r3+r4+r5+r6
	ADD r8, r8, r7			; r8=r0+r1+r2+r3+r4+r5+r6+r7

	B doGCD					; enter into function doGCD
	
doGCD
	CMP r8,r9				; if(r8 > r9)
	SUBGT r8,r8,r9			; r8=r8-r9
	SUBLT r9,r9,r8			; else if(r8 <r9) r9=r9-r8
	BNE doGCD				; if(r8 != r9), enter into function doGCD again
	
	B Finish
	
Finish
	LDMFA sp!,{r11}			; load 17
	ADD r7,r7,r11			; r7 = r7+17
	LDMFA sp!,{r11}			; load 16
	ADD r6,r6,r11			; r6 = r6+16
	LDMFA sp!,{r11}			; load 15
	ADD r5,r5,r11			; r5 = r5+15
	LDMFA sp!,{r11}			; load 14
	ADD r4,r4,r11			; r4 = r4+14
	LDMFA sp!,{r11}			; load 13
	ADD r3,r3,r11			; r3 = r3+13
	LDMFA sp!,{r11}			; load 12
	ADD r2,r2,r11			; r2 = r2+12
	LDMFA sp!,{r11}			; load 11
	ADD r1,r1,r11			; r1 = r1+11
	LDMFA sp!,{r11}			; load 10
	ADD r0,r0,r11			; r0 = r0+10
	
	STR r9,[r12],#4			; store r9 into r12
	STMFA r12!,{r0-r7}		; store r0-r7 in to stack by full ascending and update sp
	
	MOV pc, lr
	
Address1 & &00040000		;Address1=40000
	END