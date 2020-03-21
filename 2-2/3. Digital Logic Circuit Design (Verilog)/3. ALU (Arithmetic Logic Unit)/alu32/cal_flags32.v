module cal_flags32(op, result, co_add, co_prev_add, co_sub, co_prev_sub, c, n, z, v);
	input		[2:0]		op;					// 3bits input op
	input		[31:0]	result;				// 32bits input result
	input					co_add, co_prev_add, co_sub, co_prev_sub;		// 4 inputs
	output				c, n, z, v;			// 4 outputs c, n, z, v
	
	assign c = (op[2:1] != 2'b11) ? 1'b0 : ((op[0] == 1'b0) ? co_add : co_sub);	// Carry
																											// if op[0]=0, c=co_add, else c=co_sub
   assign n = result[31];				// Negative
												// check result[31]
   assign z = (result == 32'b0) ? 1'b1 : 1'b0;		//Zero
																	//if result=0, z=1, else, z=0
   assign v = (op[2:1] != 2'b11) ? 1'b0 : ((op[0] == 1'b0) ? (co_add^co_prev_add) : (co_sub^co_prev_sub));		// Overflow
																																					// if op[0]=0, v=co_add^co_prev_add
endmodule																																		// else, v= co_sub^co_prev_sub		
