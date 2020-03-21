module _dff_r(clk, reset_n, d, q);
	input clk, reset_n, d;		// 3 inputs
	output q;						// output q
	
	wire w_d;						// wire w_d
	
	_and2 U0_and2(.a(d), .b(reset_n), .y(w_d));		//instance by using AND Gate and D flipflop
	_dff U1_dff(.clk(clk), .d(w_d), .q(q));
	
endmodule
