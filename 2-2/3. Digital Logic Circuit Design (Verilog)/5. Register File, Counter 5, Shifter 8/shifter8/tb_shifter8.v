`timescale 1ns/100ps		

module tb_shifter8;				
	reg        tb_clk, tb_reset_n;	// 2 regs
	reg  [2:0] tb_op;						// 3bits reg tb_op
	reg  [1:0] tb_shamt;					// 2bits reg tb_shamt
	reg  [7:0] tb_d_in;					// 8bits reg tb_d_in
	wire [7:0] tb_d_out;					// 8bits wire tb_d_out
	
	shifter8 U0_shifter8(.clk(tb_clk), .reset_n(tb_reset_n), .op(tb_op),
	.shamt(tb_shamt), .d_in(tb_d_in), .d_out(tb_d_out)); 							// instance by using shifter8
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;			// every 5ns, invert tb_clk
	end
	
	initial
	begin		
			tb_reset_n=0; tb_op=3'b000; tb_shamt=2'b00; tb_d_in=8'b00000000;		// input
	#10;	tb_reset_n=1; tb_d_in=8'b11101110;							// every 10ns, change inputs
	#10;	tb_op=3'b001; tb_shamt=2'b01;
	#10;	tb_op=3'b010; 
	#10;	tb_op=3'b100;
	#10;	tb_shamt=2'b10; tb_op=3'b010; 
	#10;	tb_shamt=2'b01; tb_op=3'b011; 
	#10;	$stop;																// stop
	end
	
endmodule

	
	
	