`timescale 1ns/100ps

module tb_rca_clk;
	reg		clock;				//input clock
	reg [31:0] tb_a, tb_b;		//32bits 2 input
	reg		  tb_ci;				//carry in
	wire [31:0] tb_s_rca;		//32bits sum(output)
	wire			tb_co_rca;		//carry out
	
	parameter STEP = 10;			//define STEP=10ns
	
	rca_clk U0_rca_clk(.clock(clock), .a(tb_a), .b(tb_b), .ci(tb_ci), .s_rca(tb_s_rca), .co_rca(tb_co_rca));
	//express by instance
	
	always#(STEP/2) clock = ~clock;	//every 5ns, invert clock
	
	initial
	begin

		clock = 1'b1;	 tb_a = 32'h0;	 tb_b=32'h0;	tb_ci = 1'b0;							//at first, input(a,b,ci)=(0,0,0)
		#(STEP);	       tb_a = 32'hFFFF_FFFF;	 tb_b=32'h0;	tb_ci = 1'b1;				//after 10ns, input(a,b,ci)=(hFFFF_FFFF,0,1)
		#(STEP);	       tb_a = 32'h0000_FFFF;	 tb_b=32'hFFFF_0000;	tb_ci = 1'b0;		//after 10ns, input(a,b,ci)=(h0000_FFFF,hFFFF_0000,0)
		#(STEP);	       tb_a = 32'h135f_a562;	 tb_b=32'h3561_4642;	tb_ci = 1'b0;		//after 10ns, input(a,b,ci)=(h135f_a562,h3561_4642,0)
		#(STEP*2) ; 	$stop;																			//after 20ns, stop
	
	end
endmodule
