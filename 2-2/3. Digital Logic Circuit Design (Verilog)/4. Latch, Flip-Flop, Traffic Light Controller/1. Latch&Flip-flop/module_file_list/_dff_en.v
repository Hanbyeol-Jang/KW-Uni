module _dff_en(clk, en, d, q);
	input clk, en, d;		// 3 inputs
	output q;				// output q
	
	wire w_d;				// wire w_d
	
	mx2 U0_mx2(.d0(q), .d1(d), .s(en), .y(w_d));		//instance by using Multiplexer and D flipflop
	_dff U1_dff(.clk(clk), .d(w_d), .q(q));
	
endmodule
