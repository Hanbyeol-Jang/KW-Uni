module _register32(clk, d, q);
	input clk;				// input clk
	input [31:0] d;		// input 32bits d
	output [31:0] q;		// output 32bits q

	_register8 U0_register(.clk(clk), .d(d[7:0]),   .q(q[7:0]));		// instance by using 4 register8
	_register8 U1_register(.clk(clk), .d(d[15:8]),  .q(q[15:8]));
	_register8 U2_register(.clk(clk), .d(d[23:16]), .q(q[23:16]));
	_register8 U3_register(.clk(clk), .d(d[31:24]), .q(q[31:24]));

endmodule
