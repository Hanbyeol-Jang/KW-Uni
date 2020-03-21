module Factorial_Top(clk, reset_n, S_sel, S_wr, S_address, S_din, S_dout, interrupt);
	input clk, reset_n;
	input S_sel, S_wr;
	input [7:0] S_address;
	input [31:0] S_din;

	output interrupt;
	output [31:0] S_dout;

endmodule
