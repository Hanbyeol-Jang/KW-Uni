module _dff_rs_async(clk, set_n, reset_n, d, q);
	input clk, set_n, reset_n, d;		// 4 inputs
	output q;								// output q
	reg q;									// intput q
	
	always@ (posedge clk or negedge set_n or negedge reset_n)
	begin
		if(reset_n==0)		q<=1'b0;		// is reset_n=0? if yes, input 0 to q
		else if(set_n==0) q<=1'b1;		// or is set_n=0? if yes, input 1  to q
		else 					q<=d;			// unless, input d to q
	end
	
endmodule
