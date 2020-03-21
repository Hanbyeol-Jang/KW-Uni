module DMAC_Top(Clk, reset_n, M_grant, M_din, S_sel, S_wr, S_address, S_din, M_req, M_wr, M_address, M_dout, S_dout, Interrupt);
	input Clk, reset_n;					// Clock, Active low reset
	input M_grant, S_sel, S_wr;		// Master Grant,Slave Select, Write/read
	input [7:0] S_address;				// Slave Address
	input [31:0] M_din, S_din;			// Data input

	output M_req, M_wr, Interrupt;	// Request, write/read, Interrupt
	output [7:0] M_address;				// Master Address
	output [31:0] M_dout, S_dout;		// Data output
	
	wire opclear,opdone;					//wire
	wire [31:0]source, destination, size, opmode;
	wire [3:0] count;
	wire wr_en, rd_en, opstart;
	wire [2:0] state;
	wire [31:0] source1, destination1, size1;
	
	// instance by using each modules
	DMAC_slave U0_DMAC_slave(.clk(Clk), .reset_n(reset_n), .S_sel(S_sel), .S_wr(S_wr), .S_address(S_address), .S_din(S_din), .S_dout(S_dout), 
							  .Interrupt(Interrupt), .op_start(opstart), .op_clear(opclear), .sc_addr(source), .ds_addr(destination), .data_size(size),
							  .wr_en(wr_en), .data_count(count), .state(state), .opmode(opmode), .op_done(opdone));
	DMAC_master U1_DMAC_master(.clk(Clk), .reset_n(reset_n), .op_start(opstart), .op_done(opdone), .op_clear(opclear),
								 .M_req(M_req), .M_grant(M_grant), .M_wr(M_wr), .M_address(M_address), .M_dout(M_dout), .M_din(M_din),
								 .sc_addr(source1), .ds_addr(destination1), .data_size(size1), .data_count(count), .rd_en(rd_en), .state(state), .opmode(opmode));
	DMAC_fifo U2_DMAC_fifo(.clk(Clk), .reset_n(reset_n), .rd_en(rd_en), .wr_en(wr_en), .din0(source), .din1(destination), .din2(size),
							.dout0(source1), .dout1(destination1), .dout2(size1), .data_count(count), .full(), .empty(), .wr_ack(), .wr_err(), .rd_ack(), .rd_err());
										
endmodule
  