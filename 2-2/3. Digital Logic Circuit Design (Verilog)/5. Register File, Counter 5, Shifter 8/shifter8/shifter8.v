module shifter8(clk, reset_n, op, shamt, d_in, d_out);		//shifter8
	input				clk, reset_n;		// 2 inputs
	input	 [2:0]	op;					// 3bits input op
	input  [1:0]	shamt;				// 2bits input shamt
	input  [7:0]	d_in;					// 8bits input d_in
	output [7:0]	d_out;				// 8bits output d_out
	
	wire	[7:0]	do_next;					// 8bits wire do_next
	
	_register8_r U0_register8_r(.clk(clk), .reset_n(reset_n), .d(do_next), .q(d_out));					// instance by using _register8_r and cc_logic
	cc_logic U1_cc_logic(.op(op), .shamt(shamt), .d_in(d_in), .d_out(d_out), .do_next(do_next));
endmodule
