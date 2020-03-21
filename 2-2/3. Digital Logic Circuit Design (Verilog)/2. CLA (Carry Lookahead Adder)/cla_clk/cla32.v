module cla32(a, b, ci, s, co);
	input [31:0] a, b;				//32bits 2 input
	input ci;							//carry in
	output [31:0] s;					//32bits sum(output)
	output co;							//carry out
	
	wire c1, c2, c3, c4, c5, c6, c7;		//use 7 wire
	
	cla4 U0_cla4(.a(a[3:0]),   .b(b[3:0]),   .ci(ci), .s(s[3:0]),   .co(c1)); //express 32-bits CLA
	cla4 U1_cla4(.a(a[7:4]),   .b(b[7:4]),   .ci(c1), .s(s[7:4]),   .co(c2)); //by instance 8 4-bits CLA
	cla4 U2_cla4(.a(a[11:8]),  .b(b[11:8]),  .ci(c2), .s(s[11:8]),  .co(c3));
	cla4 U3_cla4(.a(a[15:12]), .b(b[15:12]), .ci(c3), .s(s[15:12]), .co(c4));
	cla4 U4_cla4(.a(a[19:16]), .b(b[19:16]), .ci(c4), .s(s[19:16]), .co(c5));
	cla4 U5_cla4(.a(a[23:20]), .b(b[23:20]), .ci(c5), .s(s[23:20]), .co(c6));
	cla4 U6_cla4(.a(a[27:24]), .b(b[27:24]), .ci(c6), .s(s[27:24]), .co(c7));
	cla4 U7_cla4(.a(a[31:28]), .b(b[31:28]), .ci(c7), .s(s[31:28]), .co(co));
	
endmodule