module mx8(a, b, c, d, e, f, g, h, s2, s1, s0, y);// 1bit 8-to-1 multiplexer
	input a, b, c, d, e, f, g, h;		// 8 inputs
	input s2, s1, s0;						// 3 inputs
	output y;								// output y
	
	wire w0, w1, w2, w3, w4, w5;		// use 6 wires
	
	mx2 U0_mx2(.d0(a),	.d1(b),	.s(s0), .y(w0));	//express
	mx2 U1_mx2(.d0(c),	.d1(d),	.s(s0), .y(w1));	//by 7 1bit 2-to-1 multiplexers
	mx2 U2_mx2(.d0(e),	.d1(f),	.s(s0), .y(w2));
	mx2 U3_mx2(.d0(g),	.d1(h),	.s(s0), .y(w3));
	mx2 U4_mx2(.d0(w0),	.d1(w1),	.s(s1), .y(w4));
	mx2 U5_mx2(.d0(w2),	.d1(w3),	.s(s1), .y(w5));
	mx2 U6_mx2(.d0(w4),	.d1(w5),	.s(s2), .y(y));
	
endmodule
