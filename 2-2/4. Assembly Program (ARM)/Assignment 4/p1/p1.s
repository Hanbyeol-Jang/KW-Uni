	AREA po, CODE, READONLY
		ENTRY
	
Start
	MOV r0, #0	;r0=0
	MOV r1, #1	;r1=1
	MOV r2, #2	;r2=2
	MOV r3, #3	;r3=3
	MOV r4, #4	;r4=4
	MOV r5, #5	;r5=5
	MOV r6, #6	;r6=6
	MOV r7, #7	;r7=7
	
	LDR sp, Address1		;load Address1 to sp
	
	STMFA sp!,{r2}			;store r2 into stack by full ascending and update sp
	STMFA sp!,{r0,r3}		;store r0,r3 into stack by full ascending and update sp
	STMFA sp!,{r5-r7}		;store r5,r6,r7 into stack by full ascending and update sp
	STMFA sp!,{r1,r4}		;store r1,r4 into stack by full ascending and update sp
	
	LDMFA sp!, {r0-r7}		;pop datas from stack by full ascending
	
	MOV pc,lr	
	
Address1 & &00040000		;Address1=40000
	END