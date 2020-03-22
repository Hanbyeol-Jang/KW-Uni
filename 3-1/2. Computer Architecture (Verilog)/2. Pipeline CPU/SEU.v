//Sign Extension Unit
module SEU(i_halfword,o_word);
  input [15:0]i_halfword;     //input 16bit data
  output [31:0]o_word;        //output 32bit data
  
  reg [31:0]o_word;
  
  //sign bit 1 : 16 bit all 1
  //sign bit 0 : 16 bit all 0
  always@(i_halfword) begin
    if(i_halfword[15]==1'b1) begin
      o_word[15:0] <= i_halfword[15:0];
      o_word[31:16] <= 16'b1111111111111111;
      end
    else begin
      o_word[15:0] <= i_halfword[15:0];
      o_word[31:16] <= 16'b0000000000000000;      
      end
  end
endmodule
