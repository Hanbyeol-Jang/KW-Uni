`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:36:28 05/01/2015 
// Design Name: 
// Module Name:    R_EX_MEM 
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
module R_EX_MEM(i_clk, i_rst_n, i_branch_pc, i_result, i_zero, i_read_data2, i_write_reg, i_WB_control, i_MEM_control,
  o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
  
  input i_clk, i_rst_n;
  input [31:0] i_branch_pc, i_result;       //input barnch pc, ALU result
  input i_zero;                             //input zero signal
  input [31:0] i_read_data2;                //input read_data(Register value)
  input [4:0] i_write_reg;                  //input write register
  input [1:0] i_WB_control;                 //input WB control
  input [2:0] i_MEM_control;                //input MEM control
  output [31:0] o_branch_pc, o_result;      //output branch pc, ALU result
  output o_zero;                            //otput zero signal
  output [31:0] o_read_data2;               //output read_data2  
  output [4:0] o_write_reg;                 //output write register
  output [1:0] o_WB_control;                //output WB control
  output [2:0] o_MEM_control;               //output MEM control
  
  reg [106:0] r_ex_mem;        //cur, next
  
  //sequental logic
  always@(posedge i_clk or negedge i_rst_n) begin
    if(i_rst_n==1'b0)
      r_ex_mem <= 107'd0;        //reset
    else
      r_ex_mem <= {i_WB_control, i_MEM_control, i_branch_pc, i_result, i_zero, i_read_data2, i_write_reg};    //not reset
  end
  
  //output combinational logic
  assign o_branch_pc 		= r_ex_mem[101:70];   
  assign o_result 			= r_ex_mem[69:38];
  assign o_zero 				= r_ex_mem[37];
  assign o_read_data2 		= r_ex_mem[36:5]; 
  assign o_write_reg 		= r_ex_mem[4:0];
  assign o_WB_control 		= r_ex_mem[106:105];
  assign o_MEM_control 		= r_ex_mem[104:102];
  
endmodule
    
