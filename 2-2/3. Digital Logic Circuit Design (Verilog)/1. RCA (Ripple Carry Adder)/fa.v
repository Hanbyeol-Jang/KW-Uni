module fa(a,b,ci,s,co);
input a,b,ci;			//input a, b, carry in
output s,co;			//output sum, carry out

wire sm,c1,c2;			//wire

ha U0_ha(.a(b),.b(ci),.s(sm),.co(c1));		//ha instance
ha U1_ha(.a(a),.b(sm),.s(s),.co(c2));		//ha instance
_or2 U2_or2(.a(c2),.b(c1),.y(co));			//_or2 instance
endmodule
