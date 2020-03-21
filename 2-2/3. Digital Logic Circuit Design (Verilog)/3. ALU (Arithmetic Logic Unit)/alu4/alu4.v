module alu4(a, b, op, result, c, n, z, v);
	input 	[3:0]		a, b;				// 4bits input a, b
	input 	[2:0]		op;				// 3bits input op	
	output	[3:0]		result;			// 4bits output result
	output				c, n, z, v;		// output c, n, z, v
	
	wire [3:0]	w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;		// 4bits 8 wires
	wire			c3_add, co_add, c3_sub, co_sub;											// 3 wires
	//express by instance
	_inv_4bits		U0_inv_4bits	(.a(a), .y(w_not_a));					// inverter Gate
	_inv_4bits		U1_inv_4bits	(.a(b), .y(w_not_b));					// inverter Gate
	_and2_4bits		U2_and2_4bits	(.a(a), .b(b), .y(w_and));				// 2 inputs AND Gate
	_or2_4bits		U3_or2_4bits	(.a(a), .b(b), .y(w_or));				// 2 inputs OR Gate
	_xor2_4bits		U4_xor2_4bits	(.a(a), .b(b), .y(w_xor));				// 2 inputs XOR Gate
	_xnor2_4bits	U5_xnor2_4bits	(.a(a), .b(b), .y(w_xnor));			// 2 inputs XNOR Gate
	cla4_ov			U6_add			(.a(a), .b(b), .ci(1'b0), .s(w_add), .c3(c3_add), .co(co_add));					// Addition
	cla4_ov			U7_sub			(.a(a), .b(w_not_b), .ci(1'b1), .s(w_sub), .c3(c3_sub), .co(co_sub));			// Subtractor
	mx8_4bits		U8_mx8_4bits	(.a(w_not_b), .b(w_not_b), .c(w_and), .d(w_or), .e(w_xor), .f(w_xnor),			// 4 bits Multiplexer
											 .g(w_add), .h(w_sub), .s2(op[2]), .s1(op[1]), .s0(op[0]), .y(result));
	cal_flags4		U9_cal_flags2  (.op(op), .result(result), .co_add(co_add), .c3_add(c3_add), .co_sub(co_sub),
											 .c3_sub(c3_sub), .c(c), .n(n), .z(z), .v(v));											//express 4 flags by instance
	
endmodule
	