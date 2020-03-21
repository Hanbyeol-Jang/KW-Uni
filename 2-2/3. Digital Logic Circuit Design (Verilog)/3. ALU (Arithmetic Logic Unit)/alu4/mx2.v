module mx2(d0, d1, s, y);  //1bit 2-to-1 Multiplexer
	input d0, d1;				// input d0, d1
	input s;						// input s
	output y;					// output y
	
	wire sb, w0, w1;			// use 3 wires sb, w0, w1
	_inv		U0_inv(.a(s), .y(sb));						//inverter Gate
	_nand2	U1_nand2(.a(d0), .b(sb), .y(w0));		// NAND Gate
	_nand2	U2_nand2(.a(d1), .b(s), .y(w1));			//	NAND Gate
	_nand2	U3_nand2(.a(w0), .b(w1), .y(y));			// NAND Gate

endmodule
