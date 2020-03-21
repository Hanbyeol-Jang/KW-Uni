module o_logic(state, La, Lb);	//output logic
	input [1:0] state;			// 2 bits input
	output[1:0] La;				// 2 bits output
	output[1:0] Lb;				// 2 bits output

	assign La[1] = state[1]; 						//La1 = q1
	assign La[0] = (~state[1]) & (state[0]);	//La0 = 'q1q0
	assign Lb[1] = (~state[1]);					//Lb1 = 'q1
	assign Lb[0] = (state[1]) & (state[0]);	//Lb0 = q1q0
endmodule
