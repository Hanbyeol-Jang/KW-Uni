	AREA pr1, CODE, READONLY   
		ENTRY
Main                                       
	LDR r0, value1                ; load value1 to r0
	LDR r1, value2                ; load value2 to r1
	LDR r12, Address1             ; load Address1 to r12
	
	MOV r8, r0, LSL#1			  ; r0 shift to left 
	CMP r8, #0					  ; compare value1 with 0 
	STREQ r1,[r12]				  ; if value1= 0, store value2
	BEQ Endline					  ; if value1= 0, go to Endline
	
	MOV r8, r1, LSL#1       	  ; r1 shift to left
	CMP r8,#0              		  ; compare value2 with 0 
	STREQ r0,[r12]          	  ; if value2= 0, store value1 
	BEQ Endline				      ; if value2= 0, go to Endline
	
	MOV lr,pc					  ; pc
	B Split_Value			      ; go to split_value
	
	TEQ r2, r5                    ; signbit ;r2^r5
	BEQ Addition               	  ; if eqaul, go to Addition
	BNE Subtraction         	  ; if not equal, go to Subtraction
         
		 
Split_Value						    ; split Value1
	MOV r2, r0, LSR#31    			; store sign bit
	MOV r3, r0, LSL#1               ; store each exponent
	MOV r3, r3, LSR#24              ; store each exponent
	MOV r4, r0, LSL#9               ; store mantissa
	MOV r4, r4, LSR#9               ; store mantissa
	ADD r4, r4, #0x800000		    ; normalize matissa
	
	MOV r5, r1, LSR#31              ; split value2
	MOV r6, r1, LSL#1               ; store sign bit
	MOV r6, r6, LSR#24              ; store each exponent
	MOV r7, r1, LSL#9               ; store each exponent
	MOV r7, r7, LSR#9               ; store mantissa
	ADD r7, r7, #0x800000			; normalize mantissa
	
	MOV pc,lr						; return to main
	
Addition                          		; when eqaul each sign bit
	CMP r3, r6                  		; compare exponent
	
	SUBGT r8, r3, r6          			; subtract smaller value from bigger one
	SUBLE r8, r6, r3          			; subtract bigger value from smaller one
	
	MOVGT r7, r7, LSR r8   				; if exponent of value1 is bigger, normalize mantissa of value2
	ADDGT r6, r6, r8          			; and adjust exponent
	MOVLE r4, r4, LSR r8  				; if exponent of value2 is bigger, normalize mantissa of value1 
	ADDLE r3, r3, r8                    ; and adjust exponent 
	
	MOV r4, r4, LSL#8					; for addition
	MOV r7, r7, LSL#8       			; for addition
	
	ADDS r9, r4, r7            			; add each mantissa, update flag
	MOVCS r9, r9, LSR#9  				; if carry updated, descend bit and then normalize mantissa again
	ADDCS r9, r9, #0x800000      		; if carry updated, descend bit and then normalize mantissa again
	ADDCS r3, r3, #1                 	; if carry updated, descend bit and then normalize mantissa again
	MOVCC r9, r9, LSR#8           		; after descending bit, normalize mantissa
	
	SUB r9, r9, #0x800000          		; normalize mantissa
	B       Cal_Result                  ; go to cal_result
         
Subtraction        						; when not eqaul each sign bit
	CMP r3, r6                       	; compare exponent
	SUBGT r8, r3, r6					; subtract smaller value from bigger one
	SUBLE r8, r6, r3					; subtract bigger value from smaller one 
	
	MOVGT r7, r7, LSR r8		 		; if exponent of value1 is bigger, normalize mantissa of value2
	ADDGT r6, r6, r8                 	; and adjust exponent 
	MOVLE r4, r4, LSR r8         		; if exponent of value2 is bigger, normalize mantissa of value1
	ADDLE r3, r3, r8                 	; and adjust exponent
	
	MOVGT r11, r2						; store sign bit of bigger exponent into r11
	MOVLE r11, r5						; store sign bit of smaller exponent into r11
	
	CMP r4, r7							; compare mantissa
	SUBGT r9, r4, r7					; subtract smaller value from bigger one
	SUBLE r9, r7, r4					; subtract bigger value from smaller one

Shift_mantissa                    		; shift mantissa           
	CMP r9,#0x800000     				; compare mantissa with operator
	MOVLO r9, r9, LSL#1  				; normalize mantissa
	ADDLO r3, r3,#-1        			; and adjust exponent
	BLO	Shift_mantissa         	  		; go to shift_mantissa for normalizing mantissa
	SUB r9, r9, #0x800000				; if normalize mantissa, subtract 1 
	B      Cal_Result               	; go to cal_result
         
Cal_Result                                 
	MOV r10, r11, LSL#31        		; sign bit
	ADD r10,r10,r3, LSL#23      		; signbit + exponent
	ADD r10,r10,r9                   	; signbit + exponent + mantissa
	STR r10,[r12]                    	; store r10 into r12
	B	Endline                       

Endline       
         MOV pc,#0

Address1 DCD   &40000        		; Address1 =& 40000
value1 DCD &bfc00000			;&41240000 ;&0		  		; store Value1
value2 DCD &40380000				;&40200000 ;&41858000	; store Value2
	
	END                                   

;41240000=>10.25
;41858000=>16.6875
;C14C0000=>-12.75