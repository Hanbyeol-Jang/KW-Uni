`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:38:34 05/01/2015 
// Design Name: 
// Module Name:    IF 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module IF(i_clk, i_rst_n, i_PCSrc, i_branch_addr, o_next_pc, o_data, jump_addr, jump, flush, w_en, pc_write);
  input i_clk, i_rst_n, i_PCSrc;      //input PCsource signal
  input [31:0] i_branch_addr, jump_addr;         //input branch address
  input jump;
  input flush, w_en;
  input pc_write;
  
  output [31:0] o_next_pc, o_data;    //output next pc, data(instruction)
  
  wire [31:0] w_o_pc, w_o_instr, w_o_sum, w_o_mux;
  
  
  PC U0_PC(i_clk, i_rst_n, w_o_mux, w_o_pc, pc_write);
  IM U1_IM(w_o_pc, w_o_instr);
  R_IF_ID U2_IF_ID(i_clk, i_rst_n, w_o_sum, w_o_instr, o_next_pc, o_data, (flush|jump), w_en);
  ADD_PC U3_ADD_PC(w_o_pc, 32'h00000004, w_o_sum);
  mux_3 U4_mux_2(w_o_sum, i_branch_addr, jump_addr, {jump ,i_PCSrc}, w_o_mux);
  
endmodule

//32bit mux_3
module mux_3(i_data1, i_data2, i_data3, sel, o_data);
  input [31:0] i_data1, i_data2, i_data3;
  input [1:0] sel;
  output reg [31:0] o_data;
  
  always@(sel,i_data1,i_data2,i_data3)
	begin
		if(sel == 2'b00) o_data <= i_data1;
		else if(sel == 2'b01) o_data <= i_data2;
		else if(sel == 2'b10) o_data <= i_data3;
		else o_data <= o_data;
	end
   
endmodule
