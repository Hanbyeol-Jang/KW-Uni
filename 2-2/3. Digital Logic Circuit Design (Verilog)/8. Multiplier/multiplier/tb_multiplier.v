`timescale 1ns/100ps	
module tb_multiplier;		
	reg tb_clk, tb_reset_n;
	reg [31:0] tb_multiplier, tb_multiplicand;		// 32 bits input
	reg tb_op_start, tb_op_clear;
	
	wire tb_op_done ;
	wire [63:0] tb_result;								//64 bits output
	
			parameter STEP = 10;
	
	//Instance Multiplier module
	multiplier U0_multiplier(.clk(tb_clk), .reset_n(tb_reset_n), .multiplier(tb_multiplier), .multiplicand(tb_multiplicand), 
									 .op_start(tb_op_start), .op_clear(tb_op_clear), .op_done(tb_op_done), .result(tb_result));

	always#(STEP/2) tb_clk = ~tb_clk;	// every 5ns, invert clk
	
	initial	//Simulation applying Input
	begin
			tb_clk = 1'b0;	tb_reset_n = 1'b0; tb_op_start = 1'b0;	tb_op_clear = 1'b0; 	tb_multiplier = 32'h0;	tb_multiplicand = 32'h0;	// initialization
																										// p: positive number, n: negative, z: zero
	#STEP; 					tb_reset_n = 1'b1;
	#STEP;	tb_multiplier = 32'h0000_0003; tb_multiplicand = 32'h0000_0005;	// when p X p, 3 X 5 = 15
	#STEP;	                       			 tb_op_start = 1'b1;
	#STEP;							             tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												 tb_op_clear = 1'b1;	// clear
	#STEP;												 tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'hFFFF_FFFB; tb_multiplicand = 32'hFFFF_FFF9;	// when n X n, -5 X -7 = 35
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'h0000_0009; tb_multiplicand = 32'hFFFF_FFFE;	// when p X n, 9 X -2 = -18
	#STEP;								tb_op_start = 1'b1;
	#STEP;								tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'hFFFF_FFFB; tb_multiplicand = 32'h0000_0005;	// when n X p, -5 X 5 = -25
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'h0000_0005; tb_multiplicand = 32'h0000_0000;	// when p X z, 5 X 0 = 0
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'h0000_0000; tb_multiplicand = 32'h0000_0005;	// when z X p, 0 X 5 = 0
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'hFFFF_FFFB; tb_multiplicand = 32'h0000_0000;	// when n X z, -5 X 0 = 0
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#STEP;	tb_multiplier = 32'h0000_0000; tb_multiplicand = 32'hFFFF_FFFB;	// when z X n, 0 X -5 = 0
	#STEP;											 tb_op_start = 1'b1;
	#STEP;											 tb_op_start = 1'b0;
	#(STEP*64);
	#STEP;												tb_op_clear = 1'b1;// clear
	#STEP;												tb_op_clear = 1'b0;
	#(STEP*3);	$stop;
	end
endmodule

