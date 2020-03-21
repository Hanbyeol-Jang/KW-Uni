module ns_logic(Ta, Tb, state, nextstate);

	parameter s0 = 2'b00;			// define s0=b'00
	parameter s1 = 2'b01;			// define s1=b'01
	parameter s2 = 2'b10;			// define s2=b'10
	parameter s3 = 2'b11;			// define s3=b'11

	input [1:0] state;				// 2 bits input
	input Ta, Tb;						// 2 inputs
	output reg [1:0] nextstate;	// 2 bits output

	always @(Ta or Tb or state)	
	begin
		case(state)
			s0 : if(Ta == 0) nextstate <= s1;		// when state = s0
					else nextstate <= s0;
			
			s1 : nextstate <= s2;						// when state = s1
	
			s2 : if(Tb == 0) nextstate <= s3;		// when state = s2
					else nextstate <= s2;
			
			s3 : nextstate <= s0;						// when state = s3
			
			default;
		endcase
	end
	
endmodule
