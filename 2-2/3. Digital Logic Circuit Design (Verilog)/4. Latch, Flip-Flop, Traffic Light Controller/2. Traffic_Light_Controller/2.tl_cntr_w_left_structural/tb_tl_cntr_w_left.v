`timescale 1ns/100ps

module tb_tl_cntr_w_left;		// Testbench of Traffic light controller with left turn signals
	reg clk, tb_reset_n;						// 2 inputs
	reg tb_Ta, tb_Tb, tb_Tal, tb_Tbl;	// 4 inputs
	wire [1:0] tb_La;							// 2bits wire
	wire [1:0] tb_Lb;							// 2bits wire

	tl_cntr_w_left U0_tl_cntr_w_left(.clk(clk), .reset_n(tb_reset_n), .Ta(tb_Ta), .Tb(tb_Tb),  // instance by using tl_cntr_w_left
												.Tal(tb_Tal), .Tbl(tb_Tbl), .La(tb_La), .Lb(tb_Lb));

	parameter STEP = 10;					// define STEP=10
	always#(STEP/2) clk = ~clk;		// every 5ns, invert clk

	initial
	begin
		clk = 0;   tb_reset_n= 1'b0; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(0,1,0,0,0)
		#(STEP-2); tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 8ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);	  tb_reset_n= 1'b1; tb_Ta=1'b0; tb_Tal=1'b0; tb_Tbl= 1'b0;						//after 10ns,input(tb_reset_n,tb_Ta,tb_Tal,tb_Tbl)=(1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b1;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,1,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b0; tb_Tb=1'b1;  tb_Tal= 1'b1; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,0,1,1,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b1;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,1,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b1;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,1)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b1; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(1,1,0,0,0)
		#(STEP);   tb_reset_n= 1'b0; tb_Ta=1'b1; tb_Tb=1'b0;  tb_Tal= 1'b0; tb_Tbl=1'b0;		//after 10ns,input(tb_reset_n,tb_Ta,tb_Tb,tb_Tal,tb_Tbl)=(0,1,0,0,0)
		#(STEP);   $stop;																							//after 10ns, stop
	end
 endmodule
 