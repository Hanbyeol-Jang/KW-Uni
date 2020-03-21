module mx4(y,d0,d1,d2,d3,s);		//4-to-1 mx
	input			d0, d1, d2, d3;	// 4 inputs
	input [1:0] s;						// 2bits input s
	output		y;						// output y
	wire 	[1:0]	w_y;					// 2bits wire w_y
	
	mx2 U0_mx2(.d0(d0), .d1(d1), .s(s[0]), .y(w_y[0]));		// instance by using 3 mx2
	mx2 U1_mx2(.d0(d2), .d1(d3), .s(s[0]), .y(w_y[1]));
	mx2 U2_mx2(.d0(w_y[0]), .d1(w_y[1]), .s(s[1]), .y(y));
	
endmodule
