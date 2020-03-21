module BUS(clk, reset_n, M0_req, M0_wr, M0_address, M0_dout, M1_req, M1_wr, M1_address, M1_dout, S0_dout, S1_dout, S2_dout, S3_dout, M0_grant, M1_grant, M_din, S0_sel, S1_sel, S2_sel, S3_sel, S_address, S_wr, S_din);
	input clk, reset_n;							// Clock, Active low reset			
	input M0_req, M0_wr, M1_req, M1_wr;		// Master 0 request & write/read, Master 1 request & write/read
	input [7:0] M0_address, M1_address;		// Master 0 & 1 address
	input [31:0] M0_dout, M1_dout;			// Master 0 & 1 data out
	input [31:0] S0_dout, S1_dout, S2_dout, S3_dout;			// Slave 0~3 data out
	
	output M0_grant, M1_grant;					// Master 0 & 1 grant
	output [31:0]M_din;							// Master data input
	output S0_sel, S1_sel, S2_sel, S3_sel, S_wr;				// Slave 0~3 select
	output [7:0] S_address;						// Slave address
	output [31:0] S_din;							// Slave data input
	
	wire [3:0] to_mx;								// wire(from ff to mx)

	// instance by using each modules
	BUS_arbiter U0_BUS_arbiter( .clk(clk), .reset_n(reset_n),.M0_req(M0_req), .M1_req(M1_req), .M0_grant(M0_grant), .M1_grant(M1_grant));
	BUS_addr U1_BUS_addr(.address(S_address), .S0_sel(S0_sel), .S1_sel(S1_sel), .S2_sel(S2_sel), .S3_sel(S3_sel));
	mux2 U2_mux2(.d0(M0_wr), .d1(M1_wr), .s({M0_grant,M1_grant}), .y(S_wr));
	mux2_8bit U3_mux2_8bit(.d0(M0_address), .d1(M1_address), .s({M0_grant,M1_grant}), .y(S_address));
	mux2_32bit U4_mux2_32bit(.d0(M0_dout), .d1(M1_dout), .s({M0_grant,M1_grant}), .y(S_din));
	_dff_r U5_dff_r(.clk(clk), .reset_n(reset_n), .d({S0_sel, S1_sel, S2_sel, S3_sel}), .q(to_mx));
	mux5_32bit U6_mux5_32bit(.d0(32'b0), .d1(S0_dout), .d2(S1_dout), .d3(S2_dout), .d4(S3_dout), .s(to_mx), .y(M_din));

endmodule
