	AREA ARMex, CODE, READONLY
		ENTRY

start
	MOV r0,#1 		  ;store 1 in r0
	MOV r0,r0,LSL #1  ;r0= r0*2 = 1*2 = 2
	MOV r0,r0, LSL #1 ;r0= r0*2 = 2*2 = 4
	MOV r0,r0, LSL #1 ;r0= r0*2 = 4*2 = 8
	
	MOV r1,#1		  ;store 1 in r1
	MOV r1,r1, LSL #1 ;r1= r1*2 = 1*2 = 2
	
	MOV r2,#1		  ;r2=1
	
	ADD r3,r0,r1	  ;r3=r0+r1=8+2=10
	
	ADD r3,r3,r2	  ;r3=r3+r2=10+1=11
	ADD r4,r4,r3      ;r4=r4+r3=11
	
	ADD r3, r3, r1    ;r3=r3+2=13
	ADD r4, r4, r3	  ;r4=r4+r3=11+13
	
	ADD r3, r3, r1 	  ;r3=r3+2=15
	ADD r4, r4, r3 	  ;r4=r4+r3=11+13+15
	
	ADD r3, r3, r1 	  ;r3=r3+2=17
	ADD r4, r4, r3    ;r4=r4+r3=11+13+15+17
	
	ADD r3, r3, r1 	  ;r3=r3+2=19
	ADD r4, r4, r3	  ;r4=r4+r3=11+13+15+17+19
	
	ADD r3, r3, r1 	  ;r3=r3+2=21
	ADD r4, r4, r3	  ;r4=r4+r3=11+13+15+17+19+21
	
	ADD r3, r3, r1 	  ;r3=r3+2=23
	ADD r4, r4, r3	  ;r4=r4+r3=11+13+15+17+19+21+23
	
	ADD r3, r3, r1 	  ;r3=r3+2=25
	ADD r4, r4, r3    ;r4=r4+r3=11+13+15+17+19+21+23+25
	
	ADD r3, r3, r1    ;r3=r3+2=27
	ADD r4, r4, r3    ;r4=r4+r3=11+13+15+17+19+21+23+25+27
	
	ADD r3, r3, r1 	  ;r3=r3+2=29
	ADD r4, r4, r3    ;r4=r4+r3=11+13+15+17+19+21+23+25+27+29
	
	LDR r5, Address1  ;load Adress1 in r5
	STR r4, [r5]      ;store r4 in r5
	
	MOV pc, lr
	
Address1 & &4000