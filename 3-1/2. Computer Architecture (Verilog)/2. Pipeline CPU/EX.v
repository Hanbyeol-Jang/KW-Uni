`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:30:46 05/01/2015 
// Design Name: 
// Module Name:    EX 
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
module EX(i_clk, i_rst_n, i_next_pc, i_read_data1, i_read_data2, i_imm, i_tar_reg, i_des_reg, i_WB_control, i_MEM_control, i_EX_control,
  o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
  
  input i_clk, i_rst_n;
  input [31:0] i_next_pc, i_read_data1, i_read_data2, i_imm;      //intput next_pc, read_data1, read_data2, immediate       
  input [4:0] i_tar_reg, i_des_reg;                               //input target register, destination register
  input [1:0] i_WB_control;                                       //input WB control
  input [2:0] i_MEM_control;                                      //intput MEM control
  input [3:0] i_EX_control;                                       //input EX control
  output [31:0] o_branch_pc, o_result;                            //output branch pc, ALU result
  output o_zero;                                                  //output zero signal
  output [31:0] o_read_data2;                                     //output read_data2
  output [4:0] o_write_reg;                                       //output write register
  output [1:0] o_WB_control;                                      //output Wb control
  output [2:0] o_MEM_control;                                     //output MEM control
  
  
  wire [31:0] w_o_branch_pc;
  wire [31:0] w_o_ALUSrc_mux;
  wire [3:0] ALU_control_input;
  wire [4:0] w_write_reg;
  
  wire w_o_zero;
  wire [31:0] w_o_result;

 // wire [31:0] w_i_imm;
  
  ALU U0_ALU(i_read_data1, w_o_ALUSrc_mux, i_imm[10:6], ALU_control_input, w_o_result, w_o_zero);
  R_EX_MEM U1_EX_MEM(i_clk, i_rst_n, w_o_branch_pc, w_o_result ,w_o_zero, i_read_data2, w_write_reg, i_WB_control, i_MEM_control, 
  o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
  ADD_PC U2_ADD_PC(i_next_pc, (i_imm<<2), w_o_branch_pc);
  mux2_32bit U3_ALUSrc_mux(i_read_data2, i_imm, i_EX_control[3], w_o_ALUSrc_mux);
  ALUControl U4_ALUControl(i_imm[5:0], i_EX_control[2:1], ALU_control_input);
  mux2_5bit U5_RegDst_mux(i_tar_reg, i_des_reg, i_EX_control[0], w_write_reg);  
 // shift_left U6_shift_left(i_imm, w_i_imm);
  
endmodule

	
	//32bit mux_2
module mux2_32bit(i_data1, i_data2, sel, o_data);
  input [31:0] i_data1, i_data2;
  input sel;
  output [31:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule
  
  //5bit mux_2
module mux2_5bit(i_data1, i_data2, sel, o_data);
  input [4:0] i_data1, i_data2;
  input sel;
  output [4:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule