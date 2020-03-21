module _dff_4_r(clk, reset_n, d, q); //4bit resettable flip flop
	input clk, reset_n;					 // 2inputs
	input [3:0]	d;							 // 4bits input
	output [3:0] q;						 // 4bits output
	reg [3:0] q;							 // 4bits reg
	
	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n == 0)	q <= 1'b0;						// if reset = 0, q is always 0
		else 					q <= d;							// otherwise q=d
	end
	
endmodule
