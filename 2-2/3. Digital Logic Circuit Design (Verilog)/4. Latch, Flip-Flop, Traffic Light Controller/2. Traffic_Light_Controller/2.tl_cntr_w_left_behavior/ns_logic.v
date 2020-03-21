module ns_logic(Ta, Tb, Tal, Tbl, state, nextstate);
	input [2:0] state;				// 3bits input
	input Ta, Tb, Tal, Tbl;			// 4 inputs
	output reg[2:0] nextstate;		// 3bits output

	parameter s0 = 3'b000;		// define s0=b'000
	parameter s1 = 3'b001;		// define s1=b'001
	parameter s2 = 3'b010;		// define s2=b'010
	parameter s3 = 3'b011;		// define s3=b'011
	parameter s4 = 3'b100;		// define s4=b'100
	parameter s5 = 3'b101;		// define s5=b'101
	parameter s6 = 3'b110;		// define s6=b'110
	parameter s7 = 3'b111;		// define s7=b'111

	always@ (state or Ta or Tb or Tal or Tbl)
	begin
		case(state)
			s0 : if(Ta == 1'b0) nextstate <= s1;	// when state=s0
					else nextstate <= s0;
			
			s1 : nextstate <= s2;						// when state=s1
			
			s2 : if(Tal == 1'b0) nextstate<= s3;	// when state=s2
					else nextstate <= s2;
			
			s3 : nextstate<= s4;							// when state=s3
		
			s4 : if(Tb == 1'b0) nextstate<= s5;		// when state=s4
					else nextstate <= s4;
			
			s5 : nextstate<= s6;							// when state=s5
			
			s6 : if(Tbl == 1'b0) nextstate<= s7;	// when state=s6
					else nextstate <= s6;
			
			s7 : nextstate<= s0;							// when state=s7
			default;
		endcase
	end
			
endmodule
