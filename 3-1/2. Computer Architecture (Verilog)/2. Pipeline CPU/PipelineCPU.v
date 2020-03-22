`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:33:09 05/01/2015 
// Design Name: 
// Module Name:    PipelineCPU 
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
module PipelineCPU( i_clk, i_rst_n, o_write_data
    );
	 
	 input i_clk, i_rst_n;
	 output [31:0] o_write_data;
	 
  // IF
  wire [31:0] w_o_next_pc, w_o_data;
  // ID
  wire [31:0] w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm;
  wire [4:0] w_o_tar_reg, w_o_des_reg;
  wire [1:0] w_o_WB_control;
  wire [2:0] w_o_MEM_control;
  wire [3:0] w_o_EX_control;
  // EX
  wire [31:0] w_o_branch_pc, w_o_result;
  wire w_o_zero;
  wire [31:0] w_o_read_data_2_2;
  wire [4:0] w_o_write_reg;
  wire [1:0] w_o_WB_control_1;
  wire [2:0] w_o_MEM_control_1;
  // MEM
  wire [4:0] w_o_write_reg_MEM;
  wire [31:0] w_o_write_data, w_o_result_MEM;
  wire [1:0] w_o_WB_control_MEM;
  wire w_o_branch;
  wire [31:0] w_o_branch_pc_MEM;
 // WB 
  wire [4:0] w_o_write_reg_WB;
  wire [31:0] w_o_write_data_WB;
  wire w_o_RegWrite;

  IF U0_IF(i_clk, i_rst_n, (w_o_zero&w_o_MEM_control_1[0]), w_o_branch_pc, w_o_next_pc, w_o_data);
  
  ID U1_ID(i_clk, i_rst_n, w_o_RegWrite, w_o_next_pc, w_o_write_reg_WB, w_o_write_data_WB, w_o_data, 
  w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm, w_o_tar_reg, w_o_des_reg, w_o_WB_control, w_o_MEM_control, w_o_EX_control);


  EX U2_EX(i_clk, i_rst_n, w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm, w_o_tar_reg, w_o_des_reg, w_o_WB_control, w_o_MEM_control, w_o_EX_control,
            w_o_branch_pc, w_o_result, w_o_zero, w_o_read_data_2_2, w_o_write_reg, w_o_WB_control_1,w_o_MEM_control_1);

  
  MEM U3_MEM(i_clk, i_rst_n, w_o_branch_pc, w_o_result, w_o_zero, w_o_read_data_2_2, w_o_write_reg, w_o_WB_control_1, w_o_MEM_control_1,
    w_o_write_reg_MEM, w_o_write_data, w_o_result_MEM, w_o_WB_control_MEM, w_o_branch, w_o_branch_pc_MEM);
  
  WB U4_WB(i_clk, i_rst_n, w_o_write_reg_MEM, w_o_write_data, w_o_result_MEM, w_o_WB_control_MEM, 
  w_o_write_reg_WB, w_o_write_data_WB, w_o_RegWrite);
  
  assign o_write_data = w_o_write_data_WB;


endmodule
