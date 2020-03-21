module ha(a,b,s,co);
input a,b;           //input data
output s,co;			//output sum, carry out

_xor2 U0_xor2(.a(a),.b(b),.y(s));		//_xor2 instance
_and2 U0_and2(.a(a),.b(b),.y(co));		//_and2 instance
endmodule
