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
module EX(i_clk, i_rst_n, i_next_pc, i_read_data1, i_read_data2, i_imm, i_tar_reg, i_des_reg, i_sor_reg, i_WB_control, i_MEM_control, i_EX_control,
  o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control, FA, FB, WB_D, MEM_D, o_tar_reg, o_sor_reg, ex_flush);
  
  input i_clk, i_rst_n;
  input [31:0] i_next_pc, i_read_data1, i_read_data2, i_imm, WB_D, MEM_D;      //intput next_pc, read_data1, read_data2, immediate       
  input [4:0] i_tar_reg, i_des_reg, i_sor_reg;                               //input target register, destination register
  input [1:0] i_WB_control;                                       //input WB control
  input [2:0] i_MEM_control;                                      //intput MEM control
  input [3:0] i_EX_control;                                       //input EX control
  input [1:0] FA,FB;
  input ex_flush;
  
  output [31:0] o_branch_pc, o_result;                            //output branch pc, ALU result
  output o_zero;                                                  //output zero signal
  output [31:0] o_read_data2;                                     //output read_data2
  output [4:0] o_write_reg;                                       //output write register
  output [1:0] o_WB_control;                                      //output Wb control
  output [2:0] o_MEM_control;                                     //output MEM control
  output [4:0] o_tar_reg, o_sor_reg;
  
  wire [31:0] w_o_branch_pc;
  wire [31:0] w_o_ALUSrc_mux;
  wire [3:0] ALU_control_input;
  wire [4:0] w_write_reg;
  wire [1:0] mx_to_wb;
  wire [2:0] mx_to_mem;
  
  wire w_o_zero;
  wire [31:0] w_o_result;

 // wire [31:0] w_i_imm;
  wire [31:0] A_to_ALU,B_to_MX;
  
  assign o_tar_reg = i_tar_reg;
  assign o_sor_reg = i_sor_reg;
  
  ALU U0_ALU(A_to_ALU, w_o_ALUSrc_mux, i_imm[10:6], ALU_control_input, w_o_result, w_o_zero);
  R_EX_MEM U1_EX_MEM(i_clk, i_rst_n, w_o_branch_pc, w_o_result ,w_o_zero, B_to_MX, w_write_reg, mx_to_wb, mx_to_mem, 
  o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
  ADD_PC U2_ADD_PC(i_next_pc, (i_imm<<2), w_o_branch_pc);
  mux2_32bit U3_ALUSrc_mux(B_to_MX, i_imm, i_EX_control[3], w_o_ALUSrc_mux);
  ALUControl U4_ALUControl(i_imm[5:0], i_EX_control[2:1], ALU_control_input);
  mux2_5bit U5_RegDst_mux(i_tar_reg, i_des_reg, i_EX_control[0], w_write_reg);  
  mux3_32bit U6_MUX(.i_data1(i_read_data1), .i_data2(WB_D), .i_data3(MEM_D), .sel(FA), .o_data(A_to_ALU));
  mux3_32bit U7_MUX(.i_data1(i_read_data2), .i_data2(WB_D), .i_data3(MEM_D), .sel(FB), .o_data(B_to_MX));
  mux2_2bit U8_MUX(.i_data1(i_WB_control), .i_data2(0), .sel(ex_flush), .o_data(mx_to_wb));
  mux2_3bit U9_MUX(.i_data1(i_MEM_control), .i_data2(0), .sel(ex_flush), .o_data(mx_to_mem));
 
 
 // shift_left U6_shift_left(i_imm, w_i_imm);
  
endmodule

	
	//32bit mux_2
module mux2_32bit(i_data1, i_data2, sel, o_data);
  input [31:0] i_data1, i_data2;
  input sel;
  output [31:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule

module mux2_2bit(i_data1, i_data2, sel, o_data);
  input [1:0] i_data1, i_data2;
  input sel;
  output [1:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule

module mux2_3bit(i_data1, i_data2, sel, o_data);
  input [2:0] i_data1, i_data2;
  input sel;
  output [2:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule
  
  //5bit mux_2
module mux2_5bit(i_data1, i_data2, sel, o_data);
  input [4:0] i_data1, i_data2;
  input sel;
  output [4:0] o_data;
  
  assign o_data = (sel == 1'b0) ? i_data1 : i_data2;
  
endmodule

module mux3_32bit(i_data1, i_data2, i_data3, sel, o_data);
  input [31:0] i_data1, i_data2, i_data3;
  input [1:0] sel;
  output reg[31:0] o_data;
  
  always@(sel, i_data1, i_data2, i_data3)
	begin
		if(sel == 2'b00) o_data <= i_data1;
		else if(sel == 2'b01) o_data <= i_data2;
		else if(sel == 2'b10) o_data <= i_data3;
		else o_data <= o_data;
	end
  
endmodule
