module _dff_rs(clk, set_n, reset_n, d, q);
	input clk, set_n, reset_n, d;		// 4 inputs
	output q;								// output q

	wire w_set_n, w_reset_n, w_d; 	// use 3 wires

	_inv U0_inv(.a(set_n), .y(w_set_n));				//instance by using Inverter Gate, OR Gate, AND Gate and D flipflop
	_or2 U1_or2(.a(d), .b(w_set_n), .y(w_reset_n));
	_and2 U2_and2(.a(w_reset_n), .b(reset_n), .y(w_d));
	_dff U3_dff(.clk(clk), .d(w_d), .q(q));

endmodule
