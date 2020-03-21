`timescale 1ns/100ps		

module tb_dff;										//testbench of D flip flop
	reg tb_clk, tb_d;								// 2 inputs
	wire tb_q, tb_q_bar;							// use 2 wires
	
	_dff U0_dff(.clk(tb_clk), .d(tb_d), .q(tb_q), .q_bar(tb_q_bar));		//instance by using _dff
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;		//every 5ns, invert tb_clk
	end
	
	initial
   begin						
	tb_d=1'b1;				//input(tb_d)=1
	#10; tb_d=1'b0;		//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;		//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;		//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;		//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;		//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;		//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;		//after 10ns,input(tb_d)=0
	#10; $stop;				//after 10ns,
	end
endmodule


	
	