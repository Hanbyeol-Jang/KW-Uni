module ALU(i_data1, i_data2, shamt, ALUop, o_result, o_zero);
input [31:0] i_data1, i_data2;  //input 32bit i_data1, i_data2
input [3:0] ALUop;              //input 4bit selector
input [4:0] shamt;				  //input shift 
output [31:0] o_result;         //output 32bit result
output o_zero;                  //output 1bit zero signal

wire [31:0] w_and, w_or, w_slt, w_add, w_sub, w_mx1, w_mx2, w_nor,w_SRL32, w_SLL32, w_SRA32;
wire  co_add, co_sub;

aand U0__and(i_data1, i_data2,w_and);          		       //instance and
oor U1__or(i_data1, i_data2,w_or);             		       //instance or
cla32 U2_cla32(i_data1, i_data2, 1'b0, w_add, co_add);   //instance add
cla32 U3_cla32(i_data1, ~i_data2, 1'b1, w_sub, co_sub);  //instance sub
slt U4_slt(i_data1, i_data2, w_slt);               	   //instance slt
nnor U5__nor(i_data1, i_data2, w_nor);             	   //instance nor
_SLL32 U6_SLL32(i_data2,shamt,w_SLL32);						//instance shift left logical
_SRL32 U7_SRL32(i_data2,shamt,w_SRL32);						//instance shift right logical
_SRA32 U8_SRA32(i_data2,shamt,w_SRA32);						//instance shift right Arithmetic

// o_result assignment
assign o_result=(ALUop==4'b0000)?w_and:((ALUop==4'b0001)?w_or:((ALUop==4'b0010) ? w_add:
					((ALUop==4'b0110) ? w_sub : ((ALUop==4'b0111) ? w_slt : ((ALUop==4'b1100) ? w_nor :
					((ALUop==4'b1000) ? w_SLL32 :((ALUop==4'b1001) ? w_SRL32 : ((ALUop==4'b1010) ? w_SRA32 : 32'h00000000))))))));

//zero flag
assign o_zero = (o_result == 32'b000000000) ? 1: 0;

endmodule

//set on less than
module slt(di_a,di_b,do);
  input [31:0] di_a,di_b;
  output [31:0] do;
  
  assign do=(di_a<di_b) ? 32'h00000001 : 32'h00000000;
  
endmodule

//and module  
module aand(di_a, di_b, do);
input [31:0] di_a, di_b;
output [31:0] do;

assign do = di_a & di_b;

endmodule

//or module
module oor(di_a,di_b,do);
input [31:0] di_a, di_b;
output [31:0] do;

assign do=di_a | di_b;

endmodule

//nor module
module nnor(di_a, di_b, do);
input [31:0] di_a, di_b;
output [31:0] do;

assign do = ~(di_a | di_b);

endmodule


module cla4(a, b, ci, s, co);  // cla  module
input [3:0] a, b;              //input 4bit datas
input ci;                      //input 1bit carry in
output [3:0] s;                //output 4bit sum
output co;                     //output 1bit cary out

wire c1,c2,c3;

clb4 U4_clb4(a, b, ci, c1, c2, c3, co );   // carry look ahead block instance
fa_v2 U0_fa(.a(a[0]),.b(b[0]),.ci(ci),.s(s[0]));
fa_v2 U1_fa(.a(a[1]),.b(b[1]),.ci(c1),.s(s[1]));
fa_v2 U2_fa(.a(a[2]),.b(b[2]),.ci(c2),.s(s[2]));
fa_v2 U3_fa(.a(a[3]),.b(b[3]),.ci(c3),.s(s[3]));  // fa_v2 instance

endmodule

//carry look ahead block module
module clb4(a,b,ci,c1,c2,c3,co);  
input [3:0] a, b;       //intput 4bit datas
input ci;               //input 1bit carry in
output c1,c2,c3,co;     //output 1bit 4 carry out

wire [3:0] g,p;

assign g=a&b;   // g = ab;
assign p=a|b;   // p = a+b;

assign c1 = g[0]|(p[0]&ci);                                                                    // c1 = g0+(p0 ci) 
assign c2 = g[1]|(p[1]&g[0])|(p[1]&p[0]& ci);                                                  // c2 = g1+(p1 g0) + (p1 p0 ci)
assign c3 = g[2]|(p[2]&g[1])|(p[2]&p[1]&g[0])|(p[2]&p[1]&p[0]&ci);                             // c3 = g2+(p2 g1) + (p2 p1 g0) + (p2 p1 p0 ci)
assign co = g[3]|(p[3]&g[2])|(p[3]&p[2]&g[1])|(p[3]&p[2]&p[1]&g[0])|(p[3]&p[2]&p[1]&p[0]&ci);  // co = g3+(p3 g2) + (p3 p2 g1) + (p3 p2 p1 g0) + (p2 p2 p1 p0 ci)

endmodule

//full adder module(only sum)
module fa_v2(a,b,ci,s);  
input a,b,ci;
output s;

assign s = a^b^ci;  
endmodule

module cla32(a, b, ci, s, co);  // 32_bit cla module
input [31:0] a, b;              //input 32bit datas
input ci;                       //input 1bit carry in
output [31:0] s;                //output 32bit sum
output co;                      //output 1bit carry out

wire c1,c2,c3,c4,c5,c6,c7;

cla4		 U0_cla4	(.a(a[3:0]),   .b(b[3:0]),   .ci(ci), .s(s[3:0]),   .co(c1));  // cla4 instance
cla4		 U1_cla4	(.a(a[7:4]),   .b(b[7:4]),   .ci(c1), .s(s[7:4]),   .co(c2));  // cla4 instance
cla4		 U2_cla4	(.a(a[11:8]),  .b(b[11:8]),  .ci(c2), .s(s[11:8]),  .co(c3));  // cla4 instance
cla4		 U3_cla4	(.a(a[15:12]), .b(b[15:12]), .ci(c3), .s(s[15:12]), .co(c4));  // cla4 instance
cla4		 U4_cla4	(.a(a[19:16]), .b(b[19:16]), .ci(c4), .s(s[19:16]), .co(c5));  // cla4 instance
cla4		 U5_cla4	(.a(a[23:20]), .b(b[23:20]), .ci(c5), .s(s[23:20]), .co(c6));  // cla4 instance
cla4 		U6_cla4	(.a(a[27:24]), .b(b[27:24]), .ci(c6), .s(s[27:24]), .co(c7));  // cla4 instance
cla4 		U7_cla4	(.a(a[31:28]), .b(b[31:28]), .ci(c7), .s(s[31:28]), .co(co));  // cla4 instance


endmodule

//8 to 1 mux module
module mx8(d0,d1,d2,d3,d4,d5,d6,d7,s,y);
input [31:0] d0,d1,d2,d3,d4,d5,d6,d7;       //input 32bit 8 datas
input [2:0] s;                              //input 3bit selector
output [31:0] y;                            //output 32bit data

wire [31:0] w0,w1,w2,w3,w4,w5;

mx2 mx20( w0,d0,d1,s[0]);                   //2 to 1 mux instance
mx2 mx21( w1,d2,d3,s[0]);                   //2 to 1 mux instance
mx2 mx22( w2,d4,d5,s[0]);                   //2 to 1 mux instance
mx2 mx23( w3,d6,d7,s[0]);                   //2 to 1 mux instance

mx2 mx24( w4,w0,w1,s[1]);                   //2 to 1 mux instance
mx2 mx25( w5,w2,w3,s[1]);                   //2 to 1 mux instance

mx2 mx26( y,w4,w5,s[2]);                   //2 to 1 mux instance

endmodule


//2 to 1 mux module
module mx2(y, d0, d1, s);
input [31:0]d0,d1;
input s;
output [31:0] y;

assign y=(s==0)?d0:d1;

endmodule

module _SRL32(d_in, shamt, d_out); // Logical shift Right  module
input [31:0] d_in;
input [4:0] shamt;
output reg [31:0] d_out;

always@(d_in or shamt)		// if 'd_in' or 'shamt' are changed,
begin

	d_out <= d_in>>shamt;
	
end
endmodule	
	
	
module _SLL32(d_in, shamt, d_out); // Logical shift Right  module
input [31:0] d_in;					
input [4:0] shamt;
output reg [31:0] d_out;

always@(d_in or shamt)
begin

	d_out <= d_in<<shamt;

end
endmodule	

module _SRA32(d_in, shamt, d_out); // shift Right arithmetic module
input signed [31:0] d_in;
input [4:0] shamt;
output reg [31:0] d_out;


// shift amount operation. 
always@(d_in or shamt)
begin

	d_out <= d_in>>>shamt;

end

endmodule	
