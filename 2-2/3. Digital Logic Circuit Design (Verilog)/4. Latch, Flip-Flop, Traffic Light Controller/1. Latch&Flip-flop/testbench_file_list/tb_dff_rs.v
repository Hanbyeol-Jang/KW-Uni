`timescale 1ns/100ps	

module tb_dff_rs;												//set, reset d flip flop test bench
	reg tb_clk,	tb_set_n, tb_reset_n, tb_d;			// 4 inputs
	wire tb_q;													// wire tb_q
	
	_dff_rs U0_dff_rs(.clk(tb_clk),	.set_n(tb_set_n),	.reset_n(tb_reset_n),	.d(tb_d),	.q(tb_q));  //instance by using _dff_rs
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;						//every 5ns, invert tb_clk
	end
	
	initial
   begin
	tb_d=1'b1; tb_set_n=1'b0; tb_reset_n=1'b0;		//input(tb_d,tb_set_n,tb_reset_n)=(1,0,0)
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;											//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1; tb_reset_n=1'b1;						//after 10ns,input(tb_d,tb_reset_n)=(1,1)
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;											//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1; tb_set_n=1'b1;						//after 10ns,input(tb_d,tb_set_n)=(1,1)
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;											//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;											//after 10ns,input(tb_d)=0
	#10; $stop;													//after 10ns,stop
	end
endmodule
