   AREA ARMex, CODE, READONLY
      ENTRY

start
   LDR r0,String1   	;store String1 in r0
   LDR r1,String2   	;store String2 in r1
   LDR r2, Address1 	;store Address1 in r2
   
   CMP r0, r1       	;compare r0 with r1
   
   MOVEQ r3, #"A"   	; if r0=r1, store A in r3
   MOVNE r3, #"B"   	; unless , store B in r3
   STR r3,[r2]      	; store r3 in r2
   
   MOV pc,lr        
   
String1 DCB "OMG",0 
String2 DCB "OMG",0 
Address1 & &4000
   END