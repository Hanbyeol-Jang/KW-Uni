module o_logic(state, La, Lb);
	input [2:0] state;	// 3bits input
	output[1:0] La;		// 2bits output
	output[1:0] Lb;		// 2bits output
	
	//La1 = 'q2'q1
	assign La[1] = ((~state[2])&(~state[0]));
	//La0 = 'q2'q1'q0 + 'q2q1
	assign La[0] = ((~state[2])&(~state[1])&(state[0])) | ((~state[2])&(state[1]));
	//Lb1 = q2'q0
	assign Lb[1] = ((state[2])&(~state[0]));
	//Lb0 = q2'q1q0  + q2q1
	assign Lb[0] = ((state[2])&(~state[1])&(state[0])) | ((state[2])&(state[1]));

endmodule
