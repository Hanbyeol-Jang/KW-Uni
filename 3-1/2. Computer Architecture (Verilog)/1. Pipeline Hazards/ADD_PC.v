//ADDER for PC module
module ADD_PC(i_data1,i_data2,o_sum);
  input [31:0]i_data1;      //input 32bit data
  input [31:0]i_data2;      //input 32bit data
  output [31:0]o_sum;       //output 32bit sum, not carry out
  
  cla32 U0_cla32(.a(i_data1), .b(i_data2), .ci(1'b0), .s(o_sum), .co());  //instance 32bit cla. carry in =0
  
endmodule






