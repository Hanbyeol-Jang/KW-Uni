`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:29:18 06/04/2017
// Design Name:   PipelineCPU_Hazards
// Module Name:   C:/Users/Administrator/Documents/Comgu/PipelineCPU_Hazards/tb_PipelineCPU_Hazards.v
// Project Name:  PipelineCPU_Hazards
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: PipelineCPU_Hazards
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_PipelineCPU_Hazards;

	// Inputs
	reg i_clk;
	reg i_rst_n;

	// Outputs
	wire [31:0] o_write_data;

	// Instantiate the Unit Under Test (UUT)
	PipelineCPU_Hazards uut (
		.i_clk(i_clk), 
		.i_rst_n(i_rst_n), 
		.o_write_data(o_write_data)
	);
	
	parameter STEP =10; 
	always #(STEP/2) i_clk=~i_clk;  // clock assign
	
	initial begin
		// Initialize Inputs
		i_clk = 0;
		i_rst_n = 0;
		
		#15; i_rst_n = 1;

		// Wait 100 ns for global reset to finish
		#500;
		$stop;
        
		// Add stimulus here

	end
      
endmodule

