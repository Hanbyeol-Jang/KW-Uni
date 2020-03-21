module _register2_r(clk, reset_n, d, q);
	input  clk, reset_n;		// 2 inputs
	input  [1:0] d;			// 2 bits input
	output [1:0] q;			// 2 bits output

	_dff_r_async U0_dff_r_async(.clk(clk), .reset_n(reset_n), .d(d[0]), .q(q[0]));	// instance by using 2_dff_r_async
	_dff_r_async U1_dff_r_async(.clk(clk), .reset_n(reset_n), .d(d[1]), .q(q[1]));

endmodule
