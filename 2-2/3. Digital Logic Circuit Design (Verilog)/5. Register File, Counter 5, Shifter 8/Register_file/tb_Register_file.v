`timescale 1ns/100ps	

module tb_Register_file;							
	reg tb_clk, tb_reset_n, tb_we;		// 3 regs
	reg  [2:0]  tb_wAddr, tb_rAddr;		// 3bits 2 regs
	reg  [31:0] tb_wData;					// 32bits reg tb_wData
	wire [31:0] tb_rData;					// 32bits wire tb_rData
	
	Register_file U0_Register_file(.clk(tb_clk), .reset_n(tb_reset_n), .wAddr(tb_wAddr),	// instance by using register_file
	.wData(tb_wData), .we(tb_we), .rAddr(tb_rAddr), .rData(tb_rData));
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;			//every 5ns, invert clk
	end
	
	initial
	begin	
	tb_reset_n=0; tb_we=0; tb_wAddr=3'b000; tb_rAddr=3'b000; tb_wData=31'h00000000; // input
	#10; tb_reset_n=1; tb_we=1; tb_wData=32'h11111111;		// every 10ns, change inputs
	#10; tb_wAddr=3'b001; tb_wData=32'hff00ff00;
	#10; tb_wAddr=3'b010;
	#10; tb_wAddr=3'b011; tb_wData=32'h0000ffff;
	#10; tb_rAddr=3'b001;
	#10; tb_rAddr=3'b010;
	#10; tb_rAddr=3'b011;
	#10; $stop;															// stop
	
	end
endmodule

	