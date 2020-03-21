`timescale 1ns/100ps								

module tb_register32;								//32bits register test bench
	reg          tb_clk;								// input tb_clk
	reg  [31:0]	 tb_d;								// input 32bits tb_d
	wire [31:0]	 tb_q;								// wire 32bits tb_q
	
	_register32 U0_register32(.clk(tb_clk), .d(tb_d), .q(tb_q));		//instance by using _register32
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;				//every 5ns, invert tb_clk
	end
	
	initial
   begin
							tb_d = 32'h0;          		//input(tb_d)=0
		#10; 				tb_d = 32'h0000_FFFF;		//after 10ns,input(tb_d)=0000FFFF
		#10;  			tb_d = 32'hFFFF_0000;		//after 10ns,input(tb_d)=FFFF0000
		#10; 				tb_d = 32'h135f_a562;		//after 10ns,input(tb_d)=135fa562
		#10; 				tb_d = 32'h3561_4642;		//after 10ns,input(tb_d)=35614642
		#10; $stop;											//after 10ns,stop
	end
endmodule
