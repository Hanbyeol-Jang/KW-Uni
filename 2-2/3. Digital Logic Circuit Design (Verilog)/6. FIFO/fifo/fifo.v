module fifo(clk, reset_n, rd_en, wr_en, din, dout, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err);  //fifo
	input clk, reset_n, rd_en, wr_en;			// 4 inputs
	input [31:0] din;									// 32bits input din
	output [31:0]dout;								// 32bits output dout
	output full, empty;								// 2 outputs
	output wr_ack, wr_err, rd_ack, rd_err;		// 4 outputs
	output [3:0] data_count;
	
	wire[2:0] head, next_head;						// 3bits 2 wire
	wire[2:0] tail, next_tail;						// 3bits 2 wire
	wire[2:0] state, next_state;					// 3bits 2 wire
	wire[3:0] next_data_count;						// 4bits 2 wire
	wire		 we, re;									// 1bit 2 wire
	wire[31:0] to_mux, to_ff;						// 32bits 2 wire

	// instance by using _dff_3_r, fifo_ns, fifo_cal, _dff_4_r, fifo_out, Register_file, mx2_to_ff and _dff32
	_dff_3_r U0_head(.clk(clk), .reset_n(reset_n), .d(next_head), .q(head));
	_dff_3_r U1_tail(.clk(clk), .reset_n(reset_n), .d(next_tail), .q(tail));
	_dff_3_r U2_state(.clk(clk), .reset_n(reset_n), .d(next_state), .q(state));
	fifo_ns  U3_ns(.rd_en(rd_en), .wr_en(wr_en), .state(state), .data_count(data_count), .next_state(next_state));
	fifo_cal U4_cal(.state(next_state), .data_count(data_count), .head(head),
						 .tail(tail), .re(re), .we(we), .next_data_count(next_data_count), .next_head(next_head), .next_tail(next_tail));
	_dff_4_r U5_data_count(.clk(clk), .reset_n(reset_n), .d(next_data_count), .q(data_count));
	fifo_out U6_fifo_out(.state(state), .data_count(data_count), .empty(empty), .full(full),
								.rd_ack(rd_ack), .rd_err(rd_err), .wr_ack(wr_ack), .wr_err(wr_err));
	Register_file U7_register(.clk(clk), .reset_n(reset_n), .wAddr(tail), .wData(din), .we(we), .rAddr(head), .rData(to_mux));
	mx2_to_ff U8_mx2(.d0(32'h0), .d1(to_mux), .s(re), .y(to_ff));
	_dff32 U9_dff32(.clk(clk), .reset_n(reset_n), .d(to_ff), .q(dout));
  
endmodule
