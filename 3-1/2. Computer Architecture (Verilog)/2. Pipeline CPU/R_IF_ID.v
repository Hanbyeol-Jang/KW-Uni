`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:40:49 05/01/2015 
// Design Name: 
// Module Name:    R_IF_ID 
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
module R_IF_ID(i_clk, i_rst_n, i_next_pc, i_data, o_next_pc, o_data);
  input i_clk, i_rst_n;
  input [31:0] i_next_pc, i_data;       //input next pc, data
  output [31:0] o_next_pc, o_data;      //output next pc, data(instruction)
  
  reg [63:0] r_if_id;     //cur,next
  
  //ff
  always@(posedge i_clk or negedge i_rst_n) begin
    if(i_rst_n==1'b0)
      r_if_id <= 64'd0;       //reset
    else
      r_if_id <= {i_next_pc,i_data}; 
  end
  
  //output 
  assign o_next_pc = r_if_id[63:32];   
  assign o_data = r_if_id[31:0];
  
endmodule
