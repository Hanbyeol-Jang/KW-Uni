`timescale 1ns/100ps  						

module tb_dlatch;     							// TestBench of D-Latch
	reg tb_clk, tb_d;            				// 2 inputs
	wire tb_q, tb_q_bar;        				// use 2 wires

	_dlatch U0_dlatch(.clk(tb_clk), .d(tb_d), .q(tb_q), .q_bar(tb_q_bar));  //instance by using dlatch

	always
		begin
			tb_clk=0; #5; tb_clk=1; #5;	
		end
	
	initial
	begin			
			tb_d = 1'b1; 		// input(tb_d)=1
	#10; 	tb_d = 1'b0;		// after 10ns, input(tb_d)=0
	#10; 	tb_d = 1'b1;		// after 10ns, input(tb_d)=1
	#10; 	tb_d = 1'b0;		// after 10ns, input(tb_d)=0
	#10; 	tb_d = 1'b1;		// after 10ns, input(tb_d)=1
	#10; 	tb_d = 1'b0;		// after 10ns, input(tb_d)=0
	#10; 	tb_d = 1'b1;		// after 10ns, input(tb_d)=1
	#10; $stop;					// after 10ns, stop
	end

endmodule
