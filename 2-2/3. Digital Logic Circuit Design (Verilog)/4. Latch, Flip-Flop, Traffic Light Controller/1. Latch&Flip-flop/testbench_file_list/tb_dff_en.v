`timescale 1ns/100ps		

module tb_dff_en;						//enabled d flip flop test bench

	reg 	tb_clk, tb_en, tb_d;		// 3inputs
	wire 	tb_q;							// wire tb_q
	
	_dff_en U0_dff_en(.clk(tb_clk), .en(tb_en), .d(tb_d), .q(tb_q));		//instance by using _dff_en
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;	//every 5ns, invert tb_clk
	end
	
	initial
   begin
	tb_en=1'b1; tb_d=1'b1;				//input(tb_en,tb_d)=(1,1)
	#10; tb_d=1'b0;						//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;						//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;						//after 10ns,input(tb_d)=0
	#10; tb_en=1'b0; tb_d=1'b1;		//after 10ns,input(tb_en,tb_d)=(0,1)
	#10; tb_d=1'b0;						//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;						//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;						//after 10ns,input(tb_d)=0
	#10; $stop;								//after 10ns,stop
	end
	
endmodule
