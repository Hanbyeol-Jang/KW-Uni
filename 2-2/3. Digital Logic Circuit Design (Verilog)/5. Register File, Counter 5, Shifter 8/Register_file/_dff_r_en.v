module _dff_r_en(clk, reset_n, en, d, q);				//reset,enable d flip flop
	input clk,reset_n, en, d;				// 4 inputs
	output reg q;								// output
	
	always@(posedge clk or negedge reset_n) begin	// when clock is rising edge or reset_n is falling edge
		if(~reset_n)	q<=1'b0;								// if reset_n=0, q=0
		else if(en)		q<=d;									// else if en exist, q=d
		else				q<=q;									// else, q=q
	end
	
endmodule
