module read_operation(Addr, Data, from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7);  //read_operation
	input  [31:0] from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7;		// 32bits 8 inputs
	input  [2:0]  Addr;			// 3bits input Addr
	output [31:0] Data;			// 32bits output Data
	
	_8_to_1_MUX U0_8_to_1_MUX(.a(from_reg0), .b(from_reg1), .c(from_reg2), .d(from_reg3),		// instance by using _8to_1_MUX
	.e(from_reg4), .f(from_reg5), .g(from_reg6), .h(from_reg7), .sel(Addr), .d_out(Data));	
	
endmodule
