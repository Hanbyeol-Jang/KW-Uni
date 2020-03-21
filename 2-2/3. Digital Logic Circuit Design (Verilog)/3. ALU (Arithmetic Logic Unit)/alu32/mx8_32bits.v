module mx8_32bits(a, b, c, d, e, f, g, h, s2, s1, s0, y);		// 32bits 8-to-1 Multiplexer
	input		[31:0]	a, b, c, d, e, f, g, h;					// 32bits 8 inputs
	input					s2, s1, s0;						// 3 inputs
	output	[31:0]	y;									// 32bits output y
	
	wire		[31:0]	w0, w1, w2, w3, w4, w5;		// use 32bits 6 wires
	
	mx2_32bits U0_mx2_32bits(.d0(a),  .d1(b),  .s(s0), .y(w0));		// express instance
   mx2_32bits U1_mx2_32bits(.d0(c),  .d1(d),  .s(s0), .y(w1));		// by using 7 mx2_32bits
   mx2_32bits U2_mx2_32bits(.d0(e),  .d1(f),  .s(s0), .y(w2));
   mx2_32bits U3_mx2_32bits(.d0(g),  .d1(h),  .s(s0), .y(w3));
   mx2_32bits U4_mx2_32bits(.d0(w0), .d1(w1), .s(s1), .y(w4));
   mx2_32bits U5_mx2_32bits(.d0(w2), .d1(w3), .s(s1), .y(w5));
   mx2_32bits U6_mx2_32bits(.d0(w4), .d1(w5), .s(s2), .y(y));
	
endmodule
