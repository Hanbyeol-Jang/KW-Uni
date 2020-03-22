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
module PipelineCPU_Hazards( i_clk, i_rst_n, o_write_data
    );
	 
	 input i_clk, i_rst_n;
	 output [31:0] o_write_data;
	 
  // IF
  wire [31:0] w_o_next_pc, w_o_data;
  // ID
  wire [31:0] w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm;
  wire [4:0] w_o_tar_reg, w_o_des_reg, w_o_sor_reg;
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
  
  wire [31:0] aluresult_to_mux;
  wire [1:0] f1_to_mx, f2_to_mx;
  wire [4:0] to_FU_s,to_FU_t, to_fu_ds;
  wire con_jump, bubble, pc_write, if_id_write;	
	
  IF U0_IF(i_clk, i_rst_n, (w_o_zero&w_o_MEM_control_1[0]), w_o_branch_pc, w_o_next_pc, w_o_data, {w_o_next_pc[31:28], w_o_data[25:0], 2'b00}, con_jump, w_o_branch, if_id_write, pc_write);
  
  ID U1_ID(i_clk, i_rst_n, w_o_RegWrite, w_o_next_pc, w_o_write_reg_WB, w_o_write_data_WB, w_o_data, 
  w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm, w_o_tar_reg, w_o_des_reg, w_o_sor_reg, w_o_WB_control, w_o_MEM_control, w_o_EX_control, w_o_branch, bubble, con_jump);


  EX U2_EX(i_clk, i_rst_n, w_o_next_pc_1, w_o_read_data_1, w_o_read_data_2, w_o_imm, w_o_tar_reg, w_o_des_reg, w_o_sor_reg,w_o_WB_control, w_o_MEM_control, w_o_EX_control,
            w_o_branch_pc, w_o_result, w_o_zero, w_o_read_data_2_2, w_o_write_reg, w_o_WB_control_1,w_o_MEM_control_1, f1_to_mx, f2_to_mx, w_o_write_data_WB, aluresult_to_mux, to_FU_t, to_FU_s, w_o_branch);

  
  MEM U3_MEM(i_clk, i_rst_n, w_o_branch_pc, w_o_result, w_o_zero, w_o_read_data_2_2, w_o_write_reg, w_o_WB_control_1, w_o_MEM_control_1,
    w_o_write_reg_MEM, w_o_write_data, w_o_result_MEM, w_o_WB_control_MEM, w_o_branch, w_o_branch_pc_MEM, aluresult_to_mux, to_fu_ds);
  
  WB U4_WB(i_clk, i_rst_n, w_o_write_reg_MEM, w_o_write_data, w_o_result_MEM, w_o_WB_control_MEM, 
  w_o_write_reg_WB, w_o_write_data_WB, w_o_RegWrite);
  
  FU U5_FU(.IDEX_Rs(to_FU_s), .IDEX_Rt(to_FU_t), .EXMEM_Rd(to_fu_ds), .EXMEM_RegWrite(w_o_WB_control_1[0]), .MEMWB_Rd(w_o_write_reg_WB), .MEMWB_RegWrite(w_o_RegWrite), .ForwardA(f1_to_mx), .ForwardB(f2_to_mx));
  HDU U6_HDU(.IDEX_Rt(to_FU_t), .IFID_Rs(w_o_data[25:21]), .IFID_Rt(w_o_data[20:16]), .IDEX_MemRead(w_o_MEM_control[1]), .EX_Bubble(bubble), .PC_Write(pc_write), .IFID_Write(if_id_write));
  
  
  assign o_write_data = w_o_write_data_WB;


endmodule
