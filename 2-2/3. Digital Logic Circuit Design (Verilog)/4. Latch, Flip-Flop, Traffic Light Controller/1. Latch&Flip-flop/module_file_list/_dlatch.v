module _dlatch(clk, d, q, q_bar);		// D latch
	input clk, d;					// 2 inputs clk, d
	output q, q_bar;				// 2 outputs q, q_bar
	wire	d_bar, r, s;			// use 3 wires
	
	_inv U0_inv(.a(d), .y(d_bar));					// instance by using Inverter Gate, 2 AND Gates and srlatch
	_and2 U1_and2(.a(clk), .b(d_bar), .y(r));	
	_and2 U2_and2(.a(d),   .b(clk),   .y(s));
	_srlatch U3_srlatch(.r(r), .s(s), .q(q), .q_bar(q_bar));
	
endmodule
