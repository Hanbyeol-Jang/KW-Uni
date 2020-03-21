module mux2_32bit(d0, d1, s, y);		//2input 32bit mux
	input [31:0] d0, d1;			// 32bits 2inputs
	input [1:0] s;					//	 select signal
	output [31:0] y;				// 32bits output
	reg [31:0] y;					// 32bits reg
	
	always @(d0, d1, s)	
	begin
		case(s)						
			2'b10		:	y <= d0;			// when M0_grant
			2'b01		:	y <= d1;			// when M1_grant
			default	:	y <= 32'bx;		// when default, unknown
		endcase
	end
endmodule
