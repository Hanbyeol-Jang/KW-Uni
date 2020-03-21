module tl_cntr_st(clk, reset_n, Ta, Tb, La, Lb);
	input clk, reset_n, Ta, Tb;		// 4 inputs
	output [1:0] La, Lb;					// 2 bits 2 input

	wire		[1:0]	next_state;			// 2bits wire
	wire		[1:0]	state;				// 2bits wire

	_register2_r U0_register2_r(.clk(clk), .reset_n(reset_n), .d(next_state), .q(state)); // instance by using register2_r, ns_logic and o_logic
	ns_logic U1_ns_logic(.Ta(Ta), .Tb(Tb), .state(state), .nextstate(next_state));
	o_logic U2_o_logic(.state(state), .La(La), .Lb(Lb));

endmodule
