module alu32(a, b, op, result, c, n, z, v);
	input 	[31:0]	a, b;				// 32 bits input a, b
	input		[2:0]		op;				// 3 bits input op
	output	[31:0]	result;			// 32bits output result
	output				c, n, z, v;		// 4 outputs c, n, z, v
	
	wire		[31:0]	w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;		// use 32bits 8 wires
	wire					co_prev_add, co_add, co_prev_sub, co_sub;		// use 4 wires
	
	_inv_32bits   U0_inv_32bits  (.a(a), .y(w_not_a));				// 32bits inverter Gate
   _inv_32bits   U1_inv_32bits  (.a(b), .y(w_not_b));				// 32bits inverter Gate
   _and2_32bits  U2_and2_32bits (.a(a), .b(b), .y(w_and));		// 32bits AND Gate
   _or2_32bits   U3_or2_32bits  (.a(a), .b(b), .y(w_or));		// 32bits OR Gate
   _xor2_32bits  U4_or2_32bits  (.a(a), .b(b), .y(w_xor));		// 32bits XOR Gate
   _xnor2_32bits U5_or2_32bits  (.a(a), .b(b), .y(w_xnor));		// 32bits XNOR Gate
   cla32_ov      U6_add         (.a(a), .b(b), .ci(1'b0), .s(w_add), .co_prev(co_prev_add), .co(co_add));			// Addition
   cla32_ov      U7_sub         (.a(a), .b(w_not_b), .ci(1'b1),.s(w_sub), .co_prev(co_prev_sub), .co(co_sub));		// Subtractor
   mx8_32bits    U8_mx8_32bits  (.y(result), .a(w_not_a), .b(w_not_b), .c(w_and), .d(w_or), .e(w_xor),			// 32bits mx8
                                 .f(w_xnor), .g(w_add), .h(w_sub), .s2(op[2]), .s1(op[1]), .s0(op[0]));                           
   cal_flags32   U9_cal_flags32 (.op(op), .result(result), .co_add(co_add), .co_prev_add(co_prev_add),			// cal_flags32
                                 .co_sub(co_sub), .co_prev_sub(co_prev_sub), .c(c), .n(n), .z(z), .v(v));
endmodule
