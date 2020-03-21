	AREA	ARMex, CODE, READONLY
			  ENTRY

start
	MOV r0, #1		;r0=1;
	MOV r1, #2		;r1=2;
	MOV r3, #3		;r3=3;
	MOV r4, #4		;r4=4;
	
	LDR r2, TEMPADDR1		;r2에 주소값 저장
	
	STRB r0, [r2]				;r2에 저장되어있는 메모리주소에 r0값 저장
	STRB r1, [r2, #1]		;r2에 저장되어있는 메모리주소에 1byte더한 메모리에 r1값 저장
	STRB r3, [r2, #2]		;r2에 저장되어있는 메모리주소에 2byte더한 메모리에 r3값 저장
	STRB r4, [r2, #3]		;r2에 저장되어있는 메모리주소에 3byte더한 메모리에 r4값 저장
	
	LDR r5, [r2]				;r2에저장되있는 주소값에있는 32bit의 메모리공간의 데이터를 r5에저장
	
	STRB r4, [r2]				;r2에 저장되어있는 메모리주소에 r4값 저장
	STRB r3, [r2, #1]		;r2에 저장되어있는 메모리주소에 1byte더한 메모리에 r3값 저장
	STRB r1, [r2, #2]		;r2에 저장되어있는 메모리주소에 2byte더한 메모리에 r1값 저장
	STRB r0, [r2, #3]		;r2에 저장되어있는 메모리주소에 3byte더한 메모리에 r0값 저장
	
	LDR r6, [r2]				;r2에저장되있는 주소값에있는 32bit의 메모리공간의 데이터를 r6에저장
	
	
TEMPADDR1	&	&00004000		;주소값 명시

	END