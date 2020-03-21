module _dff_r_async(clk, reset_n, d, q);
	input clk, reset_n, d;		// 3 inputs
	output q;						// output q
	reg q;							// input q

	always@(posedge clk or negedge reset_n)
	begin 																	
		if(reset_n==0) q<=1'b0;		// is reset_n 0? if yes, input 0 to q
		else 				q<=d;			// unless input d to q
	end
	
endmodule
