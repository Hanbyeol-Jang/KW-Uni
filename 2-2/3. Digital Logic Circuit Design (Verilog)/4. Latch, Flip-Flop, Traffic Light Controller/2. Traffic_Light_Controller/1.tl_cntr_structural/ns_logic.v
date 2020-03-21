module ns_logic(Ta, Tb, state, nextstate); 

input [1:0] state;			// 2bits input
input 		Ta, Tb;			// 2 inputs
output[1:0] nextstate;		// 2 bits output

assign nextstate[1] = state[1] ^ state[0]; 				// d1 = q1^q2
assign nextstate[0] = ((~state[1])&(~state[0])&(~Ta)) | ((state[1])&(~state[0])&(~Tb));
																		// d0 = 'q1'q0'Ta + q1'q0'Tb
endmodule
