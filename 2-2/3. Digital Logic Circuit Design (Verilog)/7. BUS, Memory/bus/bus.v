module bus(clk, reset_n, M0_req, M1_req, M0_wr, M1_wr, M0_address, M1_address, M0_dout, M1_dout, S0_dout, S1_dout, M0_grant, M1_grant, M_din, S0_sel, S1_sel, S_wr, S_address, S_din);
	input clk, reset_n;							// input clock, Active low reset			
	input M0_req, M1_req, M0_wr, M1_wr;		// Master
	input [7:0] M0_address, M1_address;	
	input [31:0] M0_dout, M1_dout;	
	input [31:0] S0_dout, S1_dout;			// Slave
	
	output M0_grant, M1_grant;					// output Master
	output [31:0] M_din;
	output S0_sel, S1_sel, S_wr;				// Slave
	output [7:0] S_address;		
	output [31:0] S_din;			
	
	wire [1:0] to_mx;								// wire(from ff to mx)
	
	// instance by using bus, mux2, mux2_8bit, mux2_32bit, bus_addr, dff_r and mux3
	bus_arbit U0_bus_arbit(.m0_req(M0_req), .m1_req(M1_req), .clk(clk), .reset_n(reset_n), .m0_grant(M0_grant), .m1_grant(M1_grant));
	mux2 U1_mux2(.d0(M0_wr), .d1(M1_wr), .s({M0_grant,M1_grant}), .y(S_wr));
	mux2_8bit U2_mux2_8bit(.d0(M0_address), .d1(M1_address), .s({M0_grant,M1_grant}), .y(S_address));
	mux2_32bit U3_mux2_32bit(.d0(M0_dout), .d1(M1_dout), .s({M0_grant,M1_grant}), .y(S_din));
	bus_addr U4_bus_addr(.address(S_address), .s0_sel(S0_sel), .s1_sel(S1_sel));
	_dff_r U5_dff_r(.clk(clk), .reset_n(reset_n), .d1(S0_sel), .d2(S1_sel), .q(to_mx));
	mux3_32bit U6_mux3_32bit(.d0(32'b0), .d1(S0_dout), .d2(S1_dout), .s(to_mx), .y(M_din));

endmodule
