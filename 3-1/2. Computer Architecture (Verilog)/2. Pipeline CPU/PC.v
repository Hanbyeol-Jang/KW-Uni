//PC module
module PC(i_clk,i_rst_n, i_next_pc,o_pc);
  input i_clk,i_rst_n;      //input 1bit clock, reset
  input [31:0] i_next_pc;   //input 32bit next_pc
  output [31:0] o_pc;       //output 32bit current_pc
  
  reg [31:0] o_pc;
  
  //sequential logic 
  //if reset, o_pc =0
  //else, o_pc = next_pc;(pc+4 or jump)
  always@ (posedge i_clk or negedge i_rst_n)begin
    if(i_rst_n==0)    o_pc = 31'd0;
    else    o_pc = i_next_pc;
end

endmodule
  
