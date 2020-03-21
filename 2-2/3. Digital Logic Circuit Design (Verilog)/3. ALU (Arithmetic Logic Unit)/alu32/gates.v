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

module _inv_4bits(a, y);			// 4bits inverter Gate
	input 	[3:0]	a;
	output 	[3:0]	y;
	assign	y=~a;
endmodule

module _and2_4bits(a, b, y);		// 4bits AND Gate
	input		[3:0]	a, b;
	output	[3:0]	y;
	assign 	y = a&b;
endmodule

module _or2_4bits(a ,b ,y);		// 4bits OR Gate
	input		[3:0]	a, b;
	output	[3:0] y;
	assign 	y = a|b;
endmodule

module _xor2_4bits(a, b, y);		// 4bits XOR Gate
	input 	[3:0]		a, b;
	output 	[3:0]		y;
	
	_xor2 U0_xor2(.a(a[0]), .b(b[0]), .y(y[0]));
	_xor2 U1_xor2(.a(a[1]), .b(b[1]), .y(y[1]));
	_xor2 U2_xor2(.a(a[2]), .b(b[2]), .y(y[2]));
	_xor2 U3_xor2(.a(a[3]), .b(b[3]), .y(y[3]));

endmodule

module _xnor2_4bits(a, b, y);		// 4bits XNOR Gate
	input 	[3:0]		a, b;
	output	[3:0]		y;
	wire		[3:0]		w0;
	
	_xor2_4bits U0_xor2_4bits(.a(a), .b(b), .y(w0));
	_inv_4bits U1_inv_4bits(.a(w0), .y(y));

endmodule

module _inv_32bits(a, y);			// 32bits inverter Gate
	input		[31:0]	a;
	output	[31:0]	y;
	assign	y = ~a;
endmodule

module _and2_32bits(a, b, y);		// 32bits AND Gate
	input		[31:0]	a, b;
	output	[31:0]	y;
	assign	y = a&b;
endmodule

module _or2_32bits(a, b, y);		// 32bits OR Gate
	input		[31:0]	a, b;
	output	[31:0]	y;
	assign	y = a|b;
endmodule

module _xor2_32bits(a, b, y);		// 32bits XOR Gate
	input 	[31:0]	a, b;
	output	[31:0]	y;
	
	_xor2_4bits U0_xor2_4bits(.a(a[3:0]), 	 .b(b[3:0]),   .y(y[3:0]));
	_xor2_4bits U1_xor2_4bits(.a(a[7:4]), 	 .b(b[7:4]),   .y(y[7:4]));
	_xor2_4bits U2_xor2_4bits(.a(a[11:8]),	 .b(b[11:8]),  .y(y[11:8]));
	_xor2_4bits U3_xor2_4bits(.a(a[15:12]), .b(b[15:12]), .y(y[15:12]));
	_xor2_4bits U4_xor2_4bits(.a(a[19:16]), .b(b[19:16]), .y(y[19:16]));
	_xor2_4bits U5_xor2_4bits(.a(a[23:20]), .b(b[23:20]), .y(y[23:20]));
	_xor2_4bits U6_xor2_4bits(.a(a[27:24]), .b(b[27:24]), .y(y[27:24]));
	_xor2_4bits U7_xor2_4bits(.a(a[31:28]), .b(b[31:28]), .y(y[31:28]));

endmodule

module _xnor2_32bits(a, b, y);		//32bits XNOR Gate
	input 	[31:0]	a, b;
	output	[31:0]	y;
	
	_xnor2_4bits U0_xnor2_4bits(.a(a[3:0]), 	 .b(b[3:0]),   .y(y[3:0]));
	_xnor2_4bits U1_xnor2_4bits(.a(a[7:4]), 	 .b(b[7:4]),   .y(y[7:4]));
	_xnor2_4bits U2_xnor2_4bits(.a(a[11:8]),	 .b(b[11:8]),  .y(y[11:8]));
	_xnor2_4bits U3_xnor2_4bits(.a(a[15:12]), .b(b[15:12]), .y(y[15:12]));
	_xnor2_4bits U4_xnor2_4bits(.a(a[19:16]), .b(b[19:16]), .y(y[19:16]));
	_xnor2_4bits U5_xnor2_4bits(.a(a[23:20]), .b(b[23:20]), .y(y[23:20]));
	_xnor2_4bits U6_xnor2_4bits(.a(a[27:24]), .b(b[27:24]), .y(y[27:24]));
	_xnor2_4bits U7_xnor2_4bits(.a(a[31:28]), .b(b[31:28]), .y(y[31:28]));

endmodule
