module mux3_32bit(d0, d1, d2, s, y); //3input 32bit mux
	input [31:0] d0, d1, d2;	// 32bits 3 inputs
	input [1:0] s;					// select signal
	output [31:0] y;				// 32bits output
	reg [31:0] y;					// 32bits reg
	
	always @(d0, d1, d2, s)
	begin
		case(s)	
			2'b00		:	y	<=	d0;	
			2'b10		:	y	<=	d1;		// when s0
			2'b01		:	y	<=	d2;		// when s1
			default	:	y	<= 32'bx;	// when default, unknown
		endcase
	end
endmodule
	