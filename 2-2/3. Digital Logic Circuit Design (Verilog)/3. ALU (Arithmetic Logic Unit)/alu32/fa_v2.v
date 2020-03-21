module fa_v2(a, b, ci, s);
input a,b,ci;					//input a,b,carry in
output s;						//output sum

wire w0;							//use 1 wire

_xor2 U0_xor2(.a(a), .b(b), .y(w0));		//XOR gate
_xor2 U1_xor2(.a(w0), .b(ci), .y(s));		//XOR gate

endmodule
