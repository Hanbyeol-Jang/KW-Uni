module _inv(a,y); //Inverter
input a;
output y;

assign y=~a;
endmodule

module _nand2(a,b,y); //nand gate
input a,b;
output y;
	
assign y=~(a&b);
endmodule

module _and2(a,b,y); //and gate
input a,b;
output y;
	
assign y=a&b;
endmodule

module _or2(a,b,y); //or gate
input a,b;
output y;
	
assign y=a|b;
endmodule

module _xor2(a,b,y);
input a,b;
output y;

wire inv_a,inv_b;
wire w0,w1;
_inv U0_inv(.a(a),.y(inv_a));		         //_inv instance
_inv U1_inv(.a(b),.y(inv_b));
_and2 U2_and2(.a(inv_a),.b(b),.y(w0));		//_and2 instance
_and2 U3_and2(.a(a),.b(inv_b),.y(w1));
_or2 U4_or2(.a(w0),.b(w1),.y(y));			//_or2 instance
endmodule
