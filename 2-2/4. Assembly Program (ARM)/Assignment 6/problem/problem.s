cr EQU 0x0D					; EQU mean "equal", cr = 0x0d

	AREA strcpy, CODE, READONLY
		ENTRY
		
Main
	LDR r0, =Table1		; load address of Table1 into r0
	LDR r1, =Table2     ; load address of Table2 into r1
	LDR r2, =CharCpy	; load address of CharCpy into r2
	
	MOV lr,pc			; lr=pc
	B COPY				; call Copy function
	MOV pc,#0			; finish
	
COPY
	STMFA sp!,{r0-r5}		; stack.push(r0-r5)

Loop
	LDRB r3, [r0], #1		; Load Table1 every 1 byte into r3
	
	CMP r3,#cr				; compare r3 with cr
	STRBEQ r6, CharCpy		; if end of Table1, store size into r6
	LDMFAEQ sp!, {r0-r5}	; stack.pop(r0-r5)
	MOVEQ pc, lr			; if end of Table1, return to Main
	
	CMP r3, #0x20			; compare r3 with #0x20(space)
	BEQ Loop				; if space, return to Loop
	STRB r3,[r1],#1			; store into r3
	ADD r6,r6,#1			; r6=r6+1
	B	Loop				; call Loop funtion

	
;================DATA AREA
	AREA Data, DATA
CharCpy						; address of arraysize
	DCB 0					; initialization
	
Table1
	DCB "Hello World", cr	; Table1
	ALIGN					; aligns the current location to a word boundary
Table2
	DCB 0					; initialization
	ALIGN					; aligns the current location to a word boundary
		
	END
	