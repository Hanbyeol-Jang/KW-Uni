module _srlatch(r, s, q, q_bar);
	input r, s;					// 2 inputs r, s
	output q, q_bar;			// 2 outputs q, q_bar
	
	_nor2 U0_nor2(.a(r), .b(q_bar), .y(q));			// instance by using 2 NOR Gate
	_nor2 U1_nor2(.a(s), .b(q),	  .y(q_bar));
	
endmodule
