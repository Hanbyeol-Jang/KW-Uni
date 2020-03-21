`timescale 1ns/100ps

module tb_memory;
	reg         tb_clk, tb_cen, tb_wen;		// 3 reg
	reg  [4:0]  tb_addr;							// 5bits reg
	reg  [31:0] tb_din;							// 32bits reg
	wire [31:0] tb_dout;							// 32bits wire
	
	memory U0_memory(.clk(tb_clk), .cen(tb_cen), .wen(tb_wen), .addr(tb_addr), .din(tb_din), .dout(tb_dout));		// instance by using memory
	
	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;				// every 5ns, invert clk
	end
	
	initial
	begin
		tb_cen=0; tb_wen=0; tb_din=32'h00; tb_addr=5'h00;			// initialization every value 0
	#10; tb_cen=1; tb_wen=1;												// after 10ns, tb_cen=1, tb_addr=1
	#10; tb_din=32'h01; tb_addr=5'h01;									// after 10ns, tb_din=1, tb_addr=1
	#10; tb_din=32'h02; tb_addr=5'h02;									// after 10ns, tb_din=2, tb_addr=2
	#10; tb_din=32'h03; tb_addr=5'h03;									// after 10ns, tb_din=3, tb_addr=3
	#10; tb_din=32'h04; tb_addr=5'h04;									// after 10ns, tb_din=4, tb_addr=4
	#10; tb_din=32'h05; tb_addr=5'h05;									// after 10ns, tb_din=5, tb_addr=5
	#10; tb_din=32'h06; tb_addr=5'h06;									// after 10ns, tb_din=6, tb_addr=6
	#10; tb_din=32'h07; tb_addr=5'h07;									// after 10ns, tb_din=7, tb_addr=7
	#10; tb_din=32'h08; tb_addr=5'h08;									// after 10ns, tb_din=8, tb_addr=8
	#10; tb_din=32'h09; tb_addr=5'h09;									// after 10ns, tb_din=9, tb_addr=9
	#10; tb_din=32'h0A; tb_addr=5'h0A;									// after 10ns, tb_din=A, tb_addr=A
	
	#10; tb_cen=0; tb_wen=0; tb_din=32'h00; tb_addr=5'h00; 		// after 10ns,
	#10; tb_cen=1;																// after 10ns,
	#10; tb_addr=5'h01;														// after 10ns,
	#10; tb_addr=5'h02;														// after 10ns,		
	#10; tb_addr=5'h03;														// after 10ns,
	#10; tb_addr=5'h04;														// after 10ns,
	#10; tb_addr=5'h05;														// after 10ns,
	#10; tb_addr=5'h06;														// after 10ns,
	#10; tb_addr=5'h07;														// after 10ns,
	#10; tb_addr=5'h08;														// after 10ns,
	#10; tb_addr=5'h09;														// after 10ns,
	#10; tb_addr=5'h0A;														// after 10ns,
	#10; tb_cen=0;tb_addr=5'h00;											// after 10ns,
	#10; $stop;																	// after 10ns,
	 
	end
endmodule
