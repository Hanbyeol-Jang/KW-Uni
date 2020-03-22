`timescale 1ns/100ps
module tb_PipelineCPU;
	reg tb_i_clk;
	reg tb_i_rst_n;
	
	wire[31:0] tb_o_write_data;

	parameter STEP =10; 
	always #(STEP/2) tb_i_clk=~tb_i_clk;  // clock assign

	PipelineCPU abcdefg(tb_i_clk, tb_i_rst_n, tb_o_write_data);

	initial
	begin
 		tb_i_clk=1'b0; tb_i_rst_n=1'b0;
 		#15; tb_i_rst_n=1'b1;
 		#500;
 		$stop;
	end

endmodule
