module _register3_r(clk, reset_n, d, q);
	input  clk, reset_n;		// 2 inputs
	input [2:0] d;				// 3bits input d
	output [2:0] q;			// 3bits output q

	_dff_r_async U0_dff_r_async(.clk(clk), .reset_n(reset_n), .d(d[0]), .q(q[0]));		// instance by using 3 _dff_r_async
	_dff_r_async U1_dff_r_async(.clk(clk), .reset_n(reset_n), .d(d[1]), .q(q[1]));
	_dff_r_async U2_dff_r_async(.clk(clk), .reset_n(reset_n), .d(d[2]), .q(q[2]));

endmodule
