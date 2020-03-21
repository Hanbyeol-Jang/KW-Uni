module _8_to_1_MUX(a, b, c, d, e, f, g, h, sel, d_out);	//_8_to_1 mux
	input [31:0] a, b, c, d, e, f, g, h;						// 32bits 8 inputs
	input [2:0]	sel;													// 3bits input sel
	output reg[31:0]d_out;											// 32bits output d_out
	
	always@(sel, a, b, c, d, e, f, g, h)begin
		case(sel)
			3'b000: d_out=a;			//when 000, d_out=a
			3'b001: d_out=b;			//when 001, d_out=b
			3'b010: d_out=c;			//when 010, d_out=c
			3'b011: d_out=d;			//when 011, d_out=d
			3'b100: d_out=e;			//when 100, d_out=e
			3'b101: d_out=f;			//when 101, d_out=f
			3'b110: d_out=g;			//when 110, d_out=g
			3'b111: d_out=h;			//when 111, d_out=h
			default:d_out=32'hx;		//when default, d_out=unknown
		endcase
	end
endmodule
