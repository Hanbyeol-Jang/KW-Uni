	AREA ARMex,CODE,READONLY
		ENTRY
		
Start
	LDR r2, Address1					;load Address1 to r2
		
	MOV r0, #1							;r0=1						=1
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
		
	ADD r0, r0,r0						;r0=1+1=2					=1*2
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
	
	ADD r0, r0, r0,LSL #1				;r0=2+2*2=6					=1*2*3
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
		
	MOV r0, r0, LSL #2					;r0=6*4=24					=1*2*3*4
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
		
	ADD r0, r0, r0, LSL #2				;r0=24+24*4=120				=1*2*3*4*5
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
		
	ADD r1, r0, r0, LSL #2				;r1=120+120*4=600
	ADD r0, r0, r1						;r0=120+600=720				=1*2*3*4*5*6
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
		
	RSB r0, r0, r0, LSL #3				;r0=720*8-720=5040			= 1*2*3*4*5*6*7
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
	
	MOV r0, r0, LSL #3 					;r0=5040*8=40320			=1*2*3*4*5*6*7*8
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
	
	ADD r0, r0, r0, LSL #3				;r0=40320*8+40320=40320*9	=1*2*3*4*5*6*7*8*9
	STR r0, [r2], #4					;store r0 in r2, r2=r2+4byte
	
	ADD r1, r0, r0, LSL #3				;r1=r0+r0*8=r0*9			=1*2*3*4*5*6*7*8*9*9													
	ADD r0, r0, r1						;r0=r0+r0*9=r0*10		 	=1*2*3*4*5*6*7*8*9*10
	STR r0, [r2]						;store r0 in r2
			
	MOV pc,lr							;pc=lr
		
Address1 & &00040000					;Address1=40000

	end
