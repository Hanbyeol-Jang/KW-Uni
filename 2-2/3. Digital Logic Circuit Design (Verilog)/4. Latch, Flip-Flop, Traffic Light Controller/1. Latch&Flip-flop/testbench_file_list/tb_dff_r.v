`timescale 1ns/100ps	

module tb_dff_r;									// testbench of Resettable D flipflop
	reg tb_clk, tb_reset_n, tb_d;				// 3 inputs
	wire tb_q;										// wire tb_q
	
	_dff_r U0_dff(.clk(tb_clk), .reset_n(tb_reset_n), .d(tb_d), .q(tb_q));  //instance by using _dff_r
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;		//every 5ns, invert tb_clk
	end
	
	initial
   begin										
	tb_d=1'b1; tb_reset_n = 1'b0;					//input(tb_d,tb_reset_n)=(1,0)
	#10; tb_d=1'b0;									//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;									//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0; tb_reset_n=1'b1;				//after 10ns,input(tb_d,tb_reset_n)=(0,1)
	#10; tb_d=1'b1;									//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;									//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;									//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;									//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1;									//after 10ns,input(tb_d)=1
	#10; tb_d=1'b0;									//after 10ns,input(tb_d)=0
	#10; tb_d=1'b1; tb_reset_n=1'b0;				//after 10ns,input(tb_d,tb_reset_n)=(1,0)
	#10; tb_d=1'b0;									//after 10ns,input(tb_d)=0
	#10; $stop;											//after 10ns,stop
	end
endmodule
