module _dff_3_r(clk, reset_n, d, q);					//3bit resettable flip flop
	input clk, reset_n;										// 2inputs
	input [2:0]	d;												// 3bits input
	output [2:0] q;											// 3bits output
	reg [2:0] q;												// 3bits reg
	
	always @ (posedge clk or negedge reset_n)			//whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n == 0)	q <= 1'b0;						// if reset = 0, q is always 0
		else 					q <= d;							// otherwise q=d
	end
	
endmodule

	