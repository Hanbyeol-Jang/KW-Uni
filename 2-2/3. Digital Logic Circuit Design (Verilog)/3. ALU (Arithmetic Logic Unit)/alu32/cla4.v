module cla4(a, b, ci, s, co);
	input [3:0] a,b;						//input a, b
	input ci;								//input carry in
	output [3:0] s;						//output sum
	output co;								//output carry out
	
	wire c1, c2, c3;						//use 3 wire
	
	clb4 U4_clb4(.a(a), .b(b), .ci(ci), .c1(c1), .c2(c2), .c3(c3), .co(co)); //express by instance
	fa_v2 U0_fa(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]));			//4 Full Adder
	fa_v2 U1_fa(.a(a[1]), .b(b[1]), .ci(c1), .s(s[1]));			//but don't need carry out
	fa_v2 U2_fa(.a(a[2]), .b(b[2]), .ci(c2), .s(s[2]));			//so use fa_v2 instead fa
	fa_v2 U3_fa(.a(a[3]), .b(b[3]), .ci(c3), .s(s[3]));
	
endmodule
