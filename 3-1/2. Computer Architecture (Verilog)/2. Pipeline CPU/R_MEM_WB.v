`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:45:23 05/01/2015 
// Design Name: 
// Module Name:    R_MEM_WB 
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
module R_MEM_WB(i_clk, i_rst_n, i_write_reg, i_write_data, i_result, i_WB_control, 
  o_write_reg, o_write_data, o_result, o_WB_control);
  
  input i_clk, i_rst_n;
  input [4:0] i_write_reg;                //input write register
  input [31:0] i_write_data, i_result;    //input write data, alu result
  input [1:0] i_WB_control;               //input WB control
  output [4:0] o_write_reg;               //output write register
  output [31:0] o_write_data, o_result;   //output write dat, alu result
  output [1:0] o_WB_control;              //output WB_control
  
  reg [70:0] r_mem_wb;   //cur, next
  
  //sequential logic
  always@(posedge i_clk or negedge i_rst_n) begin
    if(i_rst_n==1'b0)
      r_mem_wb <= 71'd0;         //reset
    else
      r_mem_wb <= {i_WB_control, i_write_data, i_result, i_write_reg};    //not reset
  end
    
  //output combinational logic
  assign o_write_reg = r_mem_wb[4:0];   
  assign o_write_data = r_mem_wb[68:37];
  assign o_result = r_mem_wb[36:5];
  assign o_WB_control = r_mem_wb[70:69]; 
    
endmodule
