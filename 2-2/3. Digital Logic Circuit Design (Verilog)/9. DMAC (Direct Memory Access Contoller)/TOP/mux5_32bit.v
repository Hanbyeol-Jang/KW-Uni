module mux5_32bit(d0, d1, d2, d3, d4, s, y);
	input [31:0] d0, d1, d2, d3, d4;	// 32bits 5 inputs
	input [3:0] s;							// select signal
	output reg [31:0] y;						// 32bits output
	
	always @(d0, d1, d2, d3, d4, s)
	begin
		case(s)	
			4'b0000		:	y = d0;	
			4'b1000		:	y = d1;		// when s0
			4'b0100		:	y = d2;		// when s1
			4'b0010		:	y = d3;		// when s2
			4'b0001		:	y = d4;		// when s3
			default		:	y = 32'bx;	// when default, unknown
		endcase
	end
endmodule
