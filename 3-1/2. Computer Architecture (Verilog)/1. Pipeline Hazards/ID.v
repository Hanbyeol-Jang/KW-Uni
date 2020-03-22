`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:25:37 05/01/2015 
// Design Name: 
// Module Name:    ID 
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
module ID(i_clk, i_rst_n, RegWrite, i_next_pc, i_write_reg, i_write_data, i_data, o_next_pc, o_read_data1, o_read_data2,
  o_imm, o_tar_reg, o_des_reg, o_sor_reg, o_WB_control, o_MEM_control, o_EX_control, id_flush, hazard_to_id, o_jump);
  
  input i_clk, i_rst_n, RegWrite;
  input [4:0] i_write_reg;                                    //input wirte register
  input [31:0] i_next_pc, i_write_data, i_data;                //input next pc, write data, data(instruction) 
  input id_flush;
  input hazard_to_id;
  
  output [31:0] o_next_pc, o_read_data1, o_read_data2, o_imm;   //output next pc, read_data1, read_data2
  output [4:0] o_tar_reg, o_des_reg, o_sor_reg;                            //output target register, destination register
  output [1:0] o_WB_control;                                    //output WB control
  output [2:0] o_MEM_control;                                   //output MEM control
  output [3:0] o_EX_control;                                    //output EX control    
  output o_jump;
  
  wire [31:0] w_o_read_data1, w_o_read_data2;
  wire w_RegDst, w_Jump, w_Branch, w_MemRead, w_MemtoReg, w_MemWrite, w_ALUSrc, w_RegWrite;
  wire [1:0] w_ALUOp;
  wire [31:0] w_o_SEU;
  wire bubble_to_mx;
  wire [8:0] mx_to_id_ex;
  
  assign bubble_to_mx = id_flush | hazard_to_id;
  
  RF U0_RF(i_clk, i_rst_n, i_data[25:21], i_data[20:16], i_write_reg, i_write_data, RegWrite, w_o_read_data1, w_o_read_data2);
  R_ID_EX U1_ID_EX(i_clk, i_rst_n, i_next_pc, w_o_read_data1, w_o_read_data2, w_o_SEU, i_data[20:16], i_data[15:11], i_data[25:21], mx_to_id_ex[8:7], mx_to_id_ex[6:4], mx_to_id_ex[3:0],
  o_next_pc, o_read_data1, o_read_data2, o_imm, o_tar_reg, o_des_reg, o_sor_reg, o_WB_control, o_MEM_control, o_EX_control);
  MainControl U2_MainControl(i_data[31:26], w_RegDst, o_jump, w_Branch, w_MemRead, w_MemtoReg, w_ALUOp, w_MemWrite, w_ALUSrc, w_RegWrite);
  SEU U3_SEU(i_data[15:0], w_o_SEU);
  mux2_9bit U4_MUX(.i_data1({w_MemtoReg, w_RegWrite, w_MemWrite, w_MemRead, w_Branch, w_ALUSrc, w_ALUOp[1], w_ALUOp[0], w_RegDst}), .i_data2(0), .sel(bubble_to_mx), .o_data(mx_to_id_ex));
  
  
endmodule

module mux2_9bit(i_data1, i_data2, sel, o_data);
  input [8:0] i_data1, i_data2;
  input sel;
  output [8:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule
