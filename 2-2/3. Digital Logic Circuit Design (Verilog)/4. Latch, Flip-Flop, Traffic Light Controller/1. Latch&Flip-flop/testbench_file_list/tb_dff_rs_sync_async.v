`timescale	1ns/100ps

module tb_dff_rs_sync_async;						//sync async set,reset d flip flop test bench
	reg 	tb_clk, tb_set_n, tb_reset_n, tb_d;	// 4 inputs
	wire 	tb_q_sync, tb_q_async;					// use 2 wires
	
	_dff_rs_sync_async U0_dff_rs_sync_async(.clk(tb_clk), .set_n(tb_set_n), .reset_n(tb_reset_n), //instance by _dff_rs_sync_async
														 .d(tb_d), .q_sync(tb_q_sync), .q_async(tb_q_async));

	always	
	begin
		tb_clk=0; #5; tb_clk=1; #5;				//every 5ns, invert tb_clk
	end
	
	initial
	begin
	tb_set_n = 1'b0; tb_reset_n = 1'b0; tb_d = 1'b0;	//input(tb_set_n,tb_reset_n)=(0,0)
	#10; tb_d = 1'b1;												//after 10ns,input(tb_d)=1
	#10; tb_d = 1'b0;												//after 10ns,input(tb_d)=0
	#10; tb_d = 1'b1;												//after 10ns,input(tb_d)=1
	#10; tb_d = 1'b0; tb_reset_n = 1'b1;					//after 10ns,input(tb_d,tb_reset_n)=(0,1)
	#10; tb_d = 1'b1;												//after 10ns,input(tb_d)=1
	#10; tb_d = 1'b0;												//after 10ns,input(tb_d)=0
	#10; tb_d = 1'b1; tb_set_n = 1'b1;						//after 10ns,input(tb_d,tb_set_n)=(1,1)
	#10; tb_d = 1'b0;												//after 10ns,input(tb_d)=0
	#10; tb_d = 1'b1;												//after 10ns,input(tb_d)=1
	#10; tb_d = 1'b0;	tb_reset_n = 1'b0;					//after 10ns,input(tb_d,tb_reset_n)=(0,0)
	#10; tb_d = 1'b1;												//after 10ns,input(tb_d)=1
	#10; $stop;														//after 10ns,stop
	end

endmodule
	