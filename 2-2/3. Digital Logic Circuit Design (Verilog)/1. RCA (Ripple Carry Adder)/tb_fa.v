`timescale 1ns/100ps		//set time

module tb_fa;
	reg tb_a, tb_b, tb_ci;		//input a, b, carry in
	wire tb_s, tb_co;			//output sum, carry out
	
	fa U0_fa(.a(tb_a), .b(tb_b), .ci(tb_ci), .s(tb_s), .co(tb_co));		//fa instance
	
	initial
	begin
	
	tb_a=0; tb_b=0; tb_ci=0;				//initializing
	#10; tb_a=0; tb_b=0; tb_ci=1;			//0+0+1
	#10; tb_a=0; tb_b=1; tb_ci=0;			//0+1+0
	#10; tb_a=0; tb_b=1; tb_ci=1;			//0+1+1
	#10; tb_a=1; tb_b=0; tb_ci=0;			//1+0+0
	#10; tb_a=1; tb_b=0; tb_ci=1;			//1+0+1
	#10; tb_a=1; tb_b=1; tb_ci=0;			//1+1+0
	#10; tb_a=1; tb_b=1; tb_ci=1;			//1+1+1
	#10; $stop;									//stop
	
	end
endmodule
