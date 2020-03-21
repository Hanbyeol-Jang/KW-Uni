module mx2_32bits(d0, d1, s, y); // 32bits 8-to-1 Multiplexer
	input		[31:0]	d0, d1;		// 32bits input d0, d1
	input					s;				// input s
	output	[31:0]	y;				// 32bits output y
	
	assign y = (s==0) ? d0 : d1;  // if s=0, y=d0
											// else , y=d1
endmodule
