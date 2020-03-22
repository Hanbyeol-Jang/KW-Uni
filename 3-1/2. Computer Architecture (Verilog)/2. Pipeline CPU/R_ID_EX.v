`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:27:21 05/01/2015 
// Design Name: 
// Module Name:    R_ID_EX 
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

module R_ID_EX(i_clk, i_rst_n, i_next_pc, i_read_data1, i_read_data2, i_imm, i_tar_reg, i_des_reg, i_WB_control, i_MEM_control, i_EX_control,
  o_next_pc, o_read_data1, o_read_data2, o_imm, o_tar_reg, o_des_reg, o_WB_control, o_MEM_control, o_EX_control);
  
  input i_clk, i_rst_n;
  input [31:0] i_next_pc, i_read_data1, i_read_data2, i_imm;    //input next_pc, read_data1, read_data2, immediate
  input [4:0] i_tar_reg, i_des_reg;                             //input target register, destination register
  input [1:0] i_WB_control;                                     //input WB control
  input [2:0] i_MEM_control;                                    //input MEM control
  input [3:0] i_EX_control;                                     //input EX control
  output [31:0] o_next_pc, o_read_data1, o_read_data2, o_imm;   //output next_pc, read_data1, read_data2, immediate
  output [4:0] o_tar_reg, o_des_reg;                            //output target register, destination register
  output [1:0] o_WB_control;                                    //output WB control 
  output [2:0] o_MEM_control;                                   //output MEM control
  output [3:0] o_EX_control;                                    //output EX control
  
  reg [146:0] r_id_ex;                            //current, next
  
  //sequence logic
  always@(posedge i_clk or negedge i_rst_n) begin
    if(i_rst_n==1'b0)
      r_id_ex <= 147'd0;                //reset
    else
      r_id_ex <= {i_WB_control,i_MEM_control,i_EX_control,i_next_pc,i_read_data1,i_read_data2,i_imm
							,i_tar_reg,i_des_reg};            
  end
  
  
  //output combinational logic
  assign o_next_pc 		= r_id_ex[137:106];   
  assign o_read_data1 	= r_id_ex[105:74];
  assign o_read_data2 	= r_id_ex[73:42]; 
  assign o_imm 			= r_id_ex[41:10];
  assign o_tar_reg		= r_id_ex[9:5];
  assign o_des_reg 		= r_id_ex[4:0];
  assign o_WB_control 	= r_id_ex[146:145];
  assign o_MEM_control 	= r_id_ex[144:142];
  assign o_EX_control 	= r_id_ex[141:138];
  
endmodule
  
  
