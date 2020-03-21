module mux2_8bit(d0, d1, s, y);		//2input 8bit mux
	input [7:0] d0, d1;	// 8bits 2 inputs
	input [1:0] s;			// select signal
	output reg [7:0] y;		// 8bits output
	
	always @(d0, d1, s)	
	begin
		case(s)	
			2'b10		:	y = d0;		// when M0_grant
			2'b01		:	y = d1;		// when M1_grant
			default	:	y = 8'bx;		// when default, unknown
		endcase
	end
endmodule
