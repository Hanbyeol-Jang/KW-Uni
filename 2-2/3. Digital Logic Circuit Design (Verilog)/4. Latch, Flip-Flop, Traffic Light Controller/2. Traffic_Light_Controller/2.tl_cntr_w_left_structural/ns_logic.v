module ns_logic(Ta, Tb, Tal, Tbl, state, nextstate);
	input [2:0] state;			// 3bits input
	input Ta, Tb, Tal, Tbl;		// 4 inputs
	output[2:0] nextstate;		// 3bits output
	
	//d2 = 'q2q1q0 + q2'q1 + q2q1'q0
	assign nextstate[2] = ((~state[2])&(state[1])&(state[0])) | ((state[2])&(~state[1])) | ((state[2])&(state[1])&(~state[0]));
	//d1 = 'q2'q1q0 + q1'q0 + q2'q1q0
	assign nextstate[1] = ((~state[2])&(~state[1])&(state[0])) | ((state[1])&(~state[0])) | ((state[2])&(~state[1])&(state[0]));
	//d1 = 'q2'q1'q0'Ta + 'q2q1'q0'Tal + q2'q1'q0'Tb + q2q1'q0'Tbl
	assign nextstate[0] = ((~state[2])&(~state[1])&(~state[0])&(~Ta)) | ((~state[2])&(state[1])&(~state[0])&(~Tal)) | 
								 ((state[2])&(~state[1])&(~state[0])&(~Tb)) | ((state[2])&(state[1])&(~state[0])&(~Tbl));
							
endmodule
