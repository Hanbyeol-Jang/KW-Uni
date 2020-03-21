module o_logic(state, La, Lb);
	input [2:0] state;		// 3bits input
	output reg[1:0] La;		// 2bits output
	output reg[1:0] Lb;		// 2bits output

	parameter s0 = 3'b000;		// define s0=b'000
	parameter s1 = 3'b001;		// define s1=b'001
	parameter s2 = 3'b010;		// define s2=b'010
	parameter s3 = 3'b011;		// define s3=b'011
	parameter s4 = 3'b100;		// define s4=b'100
	parameter s5 = 3'b101;		// define s5=b'101
	parameter s6 = 3'b110;		// define s6=b'110
	parameter s7 = 3'b111;		// define s7=b'111

	parameter red = 2'b00;		// define red=b'00
	parameter yellow = 2'b01;	// define yello=b'01
	parameter green = 2'b10;	// define green=b'10
	parameter left = 2'b11;		// define left=b'11

	always@(state)
	begin
		case(state)
			s0 : 										// when state = s0
				begin 
					La <= green; Lb <= red;		// input green to La, red to Lb
				end
			s1 : 										// when state = s1
				begin 
					La <= yellow; Lb <= red; 	// input yellow to La, red to Lb
				end
			s2 : 										// when state = s2
				begin 
					La <= left; Lb <= red;		// input left to La, red to Lb
				end
			s3 : 										// when state = s3
				begin 
					La <= yellow; Lb <= red;	// input yello to La, red to Lb
				end
			s4 : 										// when state = s4
				begin 
					La <= red; Lb <= green;		// input red to La, green to Lb
				end
			s5 :										// when state = s5
				begin 
					La <= red; Lb <= yellow;	// input red to La, yellow to Lb
				end
			s6 : 										// when state = s6
				begin 
					La <= red; Lb <= left;		// input red to La, left to Lb
				end
			s7 :										// when state = s7
				begin 
					La <= red; Lb <= yellow;	// input red to La, yello to Lb
					end
				default;
		endcase
	end
	
endmodule
