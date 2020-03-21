module _dff32(clk, reset_n, d, q);					// resettable 32bit flip flop
	input		clk, reset_n;								// 2 inputs
	input[31:0] d;											// 32bits input
	output[31:0] q;										// 32bits output
	reg [31:0]	q;											// 32bits reg
	
	always@(posedge clk or negedge reset_n)		// whenever clk is rising edge or reset is falling edge
	begin	
		if(reset_n==0) q<=32'b0;						// if reset = 0, q=0
		else q<=d;											// otherwise q=d
	end	
		
endmodule
