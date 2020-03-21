module _dff(clk, d, q, q_bar);
	input clk, d;				// 2 inputs
	output q, q_bar;			// 2 outputs
	wire clk_bar, w_q;		// use 2wires
	
	_inv U0_inv(.a(clk), .y(clk_bar));					//instance by using Inverter Gate and 2 D latch
	_dlatch U1_inv(.clk(clk_bar), .d(d), .q(w_q));
	_dlatch U2_inv(.clk(clk), .d(w_q), .q(q), .q_bar(q_bar));

endmodule
