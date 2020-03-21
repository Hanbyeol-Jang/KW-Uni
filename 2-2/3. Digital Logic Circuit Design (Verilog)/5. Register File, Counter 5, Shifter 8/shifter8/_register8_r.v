module _register8_r(clk, reset_n, d, q);		//8bit register
	input					clk, reset_n;				// 2 inputs
	input    [7:0]		d;								// 8bits input d
	output	[7:0]		q;								// 8bits output q
	
	_dff_r U0_dff_r(.clk(clk), .reset_n(reset_n), .d(d[0]), .q(q[0]));	// instance by using 8 _dff_r
	_dff_r U1_dff_r(.clk(clk), .reset_n(reset_n), .d(d[1]), .q(q[1]));
	_dff_r U2_dff_r(.clk(clk), .reset_n(reset_n), .d(d[2]), .q(q[2]));
	_dff_r U3_dff_r(.clk(clk), .reset_n(reset_n), .d(d[3]), .q(q[3]));
	_dff_r U4_dff_r(.clk(clk), .reset_n(reset_n), .d(d[4]), .q(q[4]));
	_dff_r U5_dff_r(.clk(clk), .reset_n(reset_n), .d(d[5]), .q(q[5]));
	_dff_r U6_dff_r(.clk(clk), .reset_n(reset_n), .d(d[6]), .q(q[6]));
	_dff_r U7_dff_r(.clk(clk), .reset_n(reset_n), .d(d[7]), .q(q[7]));
	
endmodule
