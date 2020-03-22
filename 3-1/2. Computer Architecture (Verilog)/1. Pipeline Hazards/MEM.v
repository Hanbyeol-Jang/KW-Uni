`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:39:30 05/01/2015 
// Design Name: 
// Module Name:    MEM 
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
module MEM(i_clk, i_rst_n, i_branch_pc, i_result, i_zero, i_read_data2, i_write_reg, i_WB_control, i_MEM_control,
  o_write_reg, o_write_data, o_result, o_WB_control, o_branch, o_branch_pc, to_exmux, to_fu_ds);
  
  input i_clk, i_rst_n;
  input [31:0] i_branch_pc, i_result;     //input branch pc, ALU result
  input i_zero;                           //input zero signal
  input [31:0] i_read_data2;              //input read_data2(register value)
  input [4:0] i_write_reg;                //input write register
  input [1:0] i_WB_control;               //input WB control
  input [2:0] i_MEM_control;              //input MEM control  
  output [4:0] o_write_reg;               //output write register
  output [31:0] o_write_data, o_result;   //output write data, ALU result
  output [1:0] o_WB_control;              //output WB contol  
  output o_branch;                        //output branch signal
  output [31:0] o_branch_pc;              //output brnach pc
  output [31:0] to_exmux;
  wire [31:0] w_o_DM_data;
  output [4:0] to_fu_ds;
  
  assign to_exmux = i_result;
  assign to_fu_ds = i_write_reg;
  
  DM U0_DM(i_clk, i_MEM_control[1], i_MEM_control[2], i_result, i_read_data2, w_o_DM_data);
  R_MEM_WB U1_MEM_WB(i_clk, i_rst_n, i_write_reg, w_o_DM_data, i_result, i_WB_control,
  o_write_reg, o_write_data, o_result, o_WB_control);
  
  //no instance
  assign o_branch_pc = i_branch_pc;
  assign o_branch = i_MEM_control[0] & i_zero;
  
endmodule
