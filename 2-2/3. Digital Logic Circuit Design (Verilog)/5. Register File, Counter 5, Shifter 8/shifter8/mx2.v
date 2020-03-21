module mx2(d0, d1, s, y);      //2 to 1 mx
	input    d0, d1;				 //2 inputs		
	input    s;						 // input s
	output    y;					 // output y

	wire sb, w0, w1;				 // 3 wires
	
	_inv     U0_inv(.a(s), .y(sb));					// instance by using _inv and 3 _nand2
	_nand2   U1_nand2(.a(d0), .b(sb), .y(w0));
	_nand2   U2_nand2(.a(d1), .b(s), .y(w1));
	_nand2   U3_nand3(.a(w0), .b(w1), .y(y));
	
endmodule
