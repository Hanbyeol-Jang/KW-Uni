//PC module
module PC(i_clk,i_rst_n, i_next_pc,o_pc, pcwrite);
  input i_clk,i_rst_n;      //input 1bit clock, reset
  input [31:0] i_next_pc;   //input 32bit next_pc
  output [31:0] o_pc;       //output 32bit current_pc
  input pcwrite;
  
  reg [31:0] o_pc;
  
  reg [31:0] c_pc;
  
  //sequential logic 
  //if reset, o_pc =0
  //else, o_pc = next_pc;(pc+4 or jump)
  always@(pcwrite, i_next_pc, c_pc, o_pc)
	begin
		if(pcwrite == 1) c_pc = i_next_pc;
		else c_pc = o_pc;
	end
  
  always@ (posedge i_clk or negedge i_rst_n)begin
    if(i_rst_n==0)    o_pc = 31'd0;
    else    o_pc = c_pc;
end

endmodule
  
