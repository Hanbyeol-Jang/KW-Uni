`timescale 1ns/100ps	

module tb_srlatch;										//testbench of SR-Latch
	reg tb_r, tb_s;										// 2 inputs
	wire tb_q, tb_q_bar;									// use 2wires
	
	_srlatch U0_srlatch(.r(tb_r), .s(tb_s), .q(tb_q), .q_bar(tb_q_bar));  // instance by using _srlatch
	
	initial
   begin
			tb_r = 1'b0; tb_s = 1'b0;	 //input (tb_r,tb_s)=(0,0)
	#10;	tb_r = 1'b1;					 //after 10ns,input(tb_r)=1
	#10; 	tb_s = 1'b1;					 //after 10ns,input(tb_s)=1
	#10; 	tb_r = 1'b0;				    //after 10ns,input(tb_r)=0
	#10; 	tb_s = 1'b0;					 //after 10ns,input(tb_s)=0
	#10; 	tb_r = 1'b1;					 //after 10ns,input(tb_r)=1
	#10; 	$stop;							 //after 10ns, stop
	end
endmodule


	
	