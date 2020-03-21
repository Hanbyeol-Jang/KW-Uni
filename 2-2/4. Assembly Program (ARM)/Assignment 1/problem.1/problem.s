	AREA	ARMex, CODE, READONLY
			 ENTRY

start
	MOV r1, #5			;r1=5
	MOV r2, #10			;r2=10
	MOV r3, #15			;r3=15
	
	LDR r0, TEMPADDR1	;r0에 주소값 저장
	
	STRB r1, [r0,#1]		;r0에저장된 주소값에 1bytes 더한 메모리에 r1값 저장
	STRB r2, [r0,#2]		;r0에저장된 주소값에 2bytes 더한 메모리에 r2값 저장
	STRB r3, [r0,#3]		;r0에저장된 주소값에 3bytes 더한 메모리에 r3값 저장
	
	LDRB r1, [r0,#1]		;r0에저장된 주소값에 1bytes 더한 메모리에 저장되있는값을 r1에 저장
	LDRB r2, [r0,#2]		;r0에저장된 주소값에 2bytes 더한 메모리에 저장되있는값을 r2에 저장
	LDRB r3, [r0,#3]		;r0에저장된 주소값에 3bytes 더한 메모리에 저장되있는값을 r3에 저장
	
	CMP	r1, #10				;r1(5)와 10이랑 비교했을때
;	CMP r2, #10				;r2(10)와 10이랑 비교했을때
;	CMP r3, #10				;r3(15)와 10이랑 비교했을때
	MOVHI r5, #1				;r1이 10보다 크면 r5에 1저장
	MOVLO r5, #2			;r1이 10보다 작으면 r5에 2저장
	MOVEQ r5, #3			;r1과 10이 같으면 r5에 3저장
	
TEMPADDR1		&		&00001000		;주소값 명시
	
	END