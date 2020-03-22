`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:47:20 05/01/2015 
// Design Name: 
// Module Name:    WB 
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
module WB(i_clk, i_rst_n, i_write_reg, i_write_data, i_result, i_WB_control, o_write_reg, o_write_data, o_RegWrite);
  input i_clk, i_rst_n;   
  input [4:0] i_write_reg;              //input write register
  input [31:0] i_write_data, i_result;  //input write data, alu result
  input [1:0] i_WB_control;             //input WB control
  output [4:0] o_write_reg;             //output write register
  output [31:0] o_write_data;           //output write data
  output o_RegWrite;                    //output RegWrite signal
  
  assign o_write_reg = i_write_reg;
  assign o_write_data = (i_WB_control[1] ==1'b0) ? i_result : i_write_data;     //32bit mux_2 with selector MemtoReg
  assign o_RegWrite = i_WB_control[0];
  
endmodule
