`timescale 1ns/100ps	

module tb_cnt5;
	reg 			tb_clk, tb_reset_n, tb_inc;		// 3 regs
	wire	[2:0]	tb_cnt;									// 3bits wire tb_cnt
	
	cnt5 U0_cnt(.cnt(tb_cnt), .clk(tb_clk), .reset_n(tb_reset_n), .inc(tb_inc));	// instance by using cnt5
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;	// every 5ns, invert clk
	end
	
	initial
	begin								
	tb_reset_n=0; tb_inc=1; // input
	#10;	tb_reset_n=1;		// every 10ns, change inputs
	#10;	tb_inc=0;
	#10;	tb_inc=1;
	#10;	
	#10;	tb_inc=0;
	#10;	tb_inc=1;
	#10;
	#10;	
	#10;
	#10;
	#10;  tb_reset_n=0;
	#10; $stop;					// stop
	
	end
	
endmodule
	