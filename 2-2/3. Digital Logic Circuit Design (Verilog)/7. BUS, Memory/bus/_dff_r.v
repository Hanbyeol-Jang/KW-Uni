module _dff_r(clk, reset_n, d1, d2, q);				// resettable flip flop
	input clk, reset_n;										// 2 inputs
	input d1,d2;												// 2 inputs
	output [1:0] q;											// 2bits output
	reg [1:0] q;												// 2bits reg
	
	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n == 0)	q <= 2'b0;						// if reset = 0, q is always 0
		else 					q <={d1,d2};					// otherwise, q={d1,d2}
	end
	
endmodule
