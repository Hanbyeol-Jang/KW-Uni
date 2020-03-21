module _dff_r(clk, reset_n, d, q);				// resettable flip flop
	input clk, reset_n;								// 2 inputs
	input [3:0] d;										// 4 inputs
	output reg [3:0] q;								// 4 bits output

	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n == 0)	q <= 4'b0000;					// if reset = 0, q is always 0
		else 					q <= d;					// otherwise, q=d
	end
endmodule
