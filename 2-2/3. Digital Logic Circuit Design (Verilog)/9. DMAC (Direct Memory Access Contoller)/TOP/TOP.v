module TOP(clk, reset_n, M0_req, M0_wr, M0_address, M0_dout, M0_grant, F_interrupt, D_interrupt, M_din);
	input clk, reset_n;			// clock, Active low reset
	input M0_req, M0_wr;			// Master request, Master write/read
	input [7:0] M0_address;		// 8bits Master address
	input [31:0]M0_dout;			// 32bits Master data output
	
	output M0_grant, F_interrupt, D_interrupt;	// Master 0 grant, FIFO interrupt, dmac interrupt
	output [31:0] M_din;			// 32bits Master data input
	
	// wire
	wire S0_sel, S1_sel, S2_sel, S3_sel, S_wr;
	wire M1_grant, M1_req, M1_wr;
	wire [7:0] S_address, M1_address;
	wire [31:0] M_din, M1_dout, S_din, S0_dout, S1_dout, S2_dout, S3_dout;

	// instance by using each modules
	ram				U0_MEMORY_0(.clk(clk), .cen(S2_sel), .wen(S_wr), .addr(S_address[3:0]), .din(S_din), .dout(S2_dout));
	ram				U1_MEMORY_1(.clk(clk), .cen(S3_sel), .wen(S_wr), .addr(S_address[3:0]), .din(S_din), .dout(S3_dout));
	BUS				U2_BUS(.clk(clk), .reset_n(reset_n), .M0_req(M0_req), .M0_wr(M0_wr), .M0_address(M0_address), .M0_dout(M0_dout), .M1_req(M1_req), .M1_wr(M1_wr), .M1_address(M1_address), .M1_dout(M1_dout), .S0_dout(S0_dout), .S1_dout(S1_dout), .S2_dout(S2_dout), .S3_dout(S3_dout), .M0_grant(M0_grant), .M1_grant(M1_grant), .M_din(M_din), .S0_sel(S0_sel), .S1_sel(S1_sel), .S2_sel(S2_sel), .S3_sel(S3_sel), .S_address(S_address), .S_wr(S_wr), .S_din(S_din)); //BUS module
	DMAC_Top       U3_DMAC(.Clk(clk), .reset_n(reset_n), .M_grant(M1_grant), .M_din(M_din), .S_sel(S0_sel), .S_wr(S_wr), .S_address(S_address), .S_din(S_din), .M_req(M1_req), .M_wr(M1_wr), .M_address(M1_address), .M_dout(M1_dout), .S_dout(S0_dout), .Interrupt(D_interrupt));
	Factorial_Top  U4_FACTORIAL(.clk(clk), .reset_n(reset_n), .S_sel(S1_sel), .S_wr(S_wr), .S_address(S_address), .S_din(S_din), .S_dout(S1_dout), .interrupt(F_interrupt));

endmodule

