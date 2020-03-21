module _inv(a,y);			//INVERTER gate
input a;
output y;
assign y=~a;
endmodule

module _nand2(a,b,y);			//NAND gate
input a,b;
output y;
assign y=~(a&b);
endmodule

module _and2(a,b,y);			//AND gate
input a,b;
output y;
assign y=a&b;
endmodule

module _or2(a,b,y);			//OR gate
input a,b;
output y;
assign y=a|b;
endmodule

module _xor2(a,b,y);			//XOR gate
input a, b;
output y;
wire inv_a, inv_b;
wire w0, w1;
_inv U0_inv(.a(a), .y(inv_a));
_inv U1_inv(.a(b), .y(inv_b));
_and2 U2_and2(.a(inv_a), .b(b), .y(w0));
_and2 U3_and2(.a(a),.b(inv_b), .y(w1));
_or2 U4_or2(.a(w0), .b(w1),.y(y));
endmodule

module _and3(a,b,c,y);		//AND gate
input a,b,c;					//3 Input
output y;
assign y=a&b&c;
endmodule

module _and4(a,b,c,d,y);		//AND gate
input a,b,c,d;						//4 Input
output y;
assign y=a&b&c&d;
endmodule

module _and5(a,b,c,d,e,y);		//AND gate
input a,b,c,d,e;					//5 Input
output y;
assign y=a&b&c&d&e;
endmodule

module _or3(a,b,c,y);			//OR gate
input a,b,c;						//3 Input
output y;
assign y=a|b|c;
endmodule

module _or4(a,b,c,d,y);			//OR gate
input a,b,c,d;						//4 Input
output y;
assign y=a|b|c|d;
endmodule

module _or5(a,b,c,d,e,y);			//OR gate
input a,b,c,d,e;						//5 Input
output y;
assign y=a|b|c|d|e;
endmodule
