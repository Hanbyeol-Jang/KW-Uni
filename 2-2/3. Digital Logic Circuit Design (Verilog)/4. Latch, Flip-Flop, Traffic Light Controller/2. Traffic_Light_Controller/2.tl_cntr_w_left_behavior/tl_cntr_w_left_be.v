module tl_cntr_w_left_be(clk, reset_n, Ta, Tb, Tal, Tbl, La, Lb);
	input clk, reset_n, Ta, Tb, Tal, Tbl;		// 6 inputs
	output [1:0] La, Lb;								// 2 bits 2 output

	wire	[2:0]	next_state;					// 3bits wire
	wire	[2:0]	state;						// 3bits wire

	_register3_r U0_register3_r(.clk(clk), .reset_n(reset_n), .d(next_state), .q(state));						//instance by using _register3_r,ns_logic and o_logic
	ns_logic U1_ns_logic(.Ta(Ta), .Tb(Tb), .Tal(Tal), .Tbl(Tbl), .state(state), .nextstate(next_state));
	o_logic U2_o_logic(.state(state), .La(La), .Lb(Lb));

endmodule
