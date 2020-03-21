module _dff_r(clk, reset_n, d, q);						//resettable d flip flop
	input clk, reset_n, d;									// 3 inputs
	output reg q;												// output leg q
	
	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is negedge
	begin
		if(reset_n == 0)q <= 1'b0;							// if reset_n=0, q=0
		else q <= d;											// else q=d
	end
	
endmodule
