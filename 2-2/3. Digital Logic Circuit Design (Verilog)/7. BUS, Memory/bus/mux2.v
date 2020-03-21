module mux2(d0, d1, s, y);		//2 input mux
	input d0, d1;		// 2 inputs
	input [1:0] s;		// select signal
	output y;			// output
	reg y;				// reg
	
	always @(d0, d1, s)	
	begin
		case(s)	
			2'b10		:	y <= d0;		// when M0_grant
			2'b01		:	y <= d1;		// when M1_grant
			default	:	y <= 1'bx;	// when default, unknown
		endcase
	end
endmodule
