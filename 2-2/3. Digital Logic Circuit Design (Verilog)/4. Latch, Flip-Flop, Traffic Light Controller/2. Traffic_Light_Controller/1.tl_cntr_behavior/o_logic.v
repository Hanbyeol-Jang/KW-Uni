module o_logic(state, La,Lb);			
	input [1:0] state;			// 2 bits input
	output reg[1:0] La;			// 2 bits output 
	output reg[1:0] Lb;			// 2 bits output

	parameter s0 = 2'b00;		// define s0=b'00
	parameter s1 = 2'b01;		// define s1=b'01
	parameter s2 = 2'b10;		// define s2=b'10
	parameter s3 = 2'b11;		// define s3=b'11

	parameter red = 2'b00;		// define red =	b'00
	parameter yellow = 2'b01;	// define yellow= b'01
	parameter green = 2'b10;	// define green =	b'10

	always @(state)
	begin
		case(state)
			s0 : begin								// when state = s0
					La <= yellow; Lb <=red;		// input yello to La, red to Lb at the same time
					end
					
			s1 :begin 								// when state = s1
					La <= red; Lb <= green;		// input red to La, green to Lb at the same time
					end
					
			s2 : begin								// when state = s2
					La <= red; Lb <=yellow;		// input red to La, yello to Lb at the same time
					end
					
			s3 : begin 								// when state = s3
					La <= green ; Lb<= red;		// input green to La, red to Lb at the same time
					end
					
			default;
		endcase
	end
	
endmodule
