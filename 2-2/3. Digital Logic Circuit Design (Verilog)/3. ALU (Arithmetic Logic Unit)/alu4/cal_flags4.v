module cal_flags4(op, result, co_add, c3_add, co_sub, c3_sub, c, n, z, v);
	input [2:0]	op;					// 3bits input op
	input [3:0]	result;				// 4bits input result
	input			co_add, c3_add, co_sub, c3_sub;		//4 inputs
	output		c, n, z, v;									//output 4 Flags Carry, Negative, Zero, Overflow
	
	assign c = (op[2:1] != 2'b11) ? 1'b0 : ((op[0] == 1'b0) ? co_add : co_sub);	// Carry
																				// if op[0]=0, c=co_add, else, c=co_sub
	assign n = result[3];		// Negative
										// check result[3]
	assign z = (result == 4'b0) ? 1'b1 : 1'b0;		// Zero
																	// if result =0, z=1 ,else, z=0
	assign v = (op[2:1] != 2'b11) ? 1'b0 : ((op[0] == 1'b0) ? (co_add^c3_add) : (co_sub^c3_sub));	//Overflow
																					// if op[0]=0, v= co_add^c3_add, else, v=co_sub^c3_sub
endmodule 
