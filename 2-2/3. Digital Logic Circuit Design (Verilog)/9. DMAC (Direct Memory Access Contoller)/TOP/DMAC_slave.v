module DMAC_slave(clk, reset_n, S_sel, S_wr, S_address, S_din, S_dout, Interrupt, op_start, op_done, op_clear, sc_addr, ds_addr, data_size, wr_en, data_count, state, opmode);
	input clk, reset_n, S_sel, S_wr, op_done;
	input [7:0] S_address;
	input [3:0] data_count;	// data count
	input [31:0] S_din;		// 32bits data in
	input [2:0] state;
	
	output reg [31:0] S_dout;
	output reg op_start, op_clear, wr_en;
	output Interrupt;
	output reg [31:0] sc_addr, ds_addr, data_size, opmode; 
	reg next_op_start, next_op_done, next_wr_en;
	reg [31:0] next_sc_addr, next_ds_addr, next_data_size, next_data_count, next_S_dout, next_Interrupt, next_op_clear;
	reg [31:0] DATA_COUNT, next_opmode, OP_DONE, INTERRUPT;
	
	parameter IDLE    = 3'b000;			// define
	parameter POP     = 3'b001;
	parameter REQUEST = 3'b010;
	parameter READ    = 3'b011;
	parameter WRITE   = 3'b100;
	parameter DONE    = 3'b101;
	
	assign Interrupt = INTERRUPT[0] & OP_DONE[0];
	
// OPERATION CLEAR Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) op_clear = 0;
		else op_clear = next_op_clear[0];
	end
	
	always@(S_sel, S_wr, S_din, op_done, S_address, op_clear)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && op_done == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000)
			next_op_clear = S_din;		// offset 0x0
		else
			next_op_clear = {31'b0, op_clear};
	end
	
// OPERATION START Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) op_start = 0;
		else op_start = next_op_start;
	end
	
	always@(S_sel, S_wr, state, S_din, S_address)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)	
			next_op_start = 1'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && state == IDLE && S_din[0] == 1'b1 && S_address[3:0] == 4'b0001)
			next_op_start = 1'b1;		// offset 0x1
		else
			next_op_start = 1'b0;
	end
		
// INTERRUPT ENABLE Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) INTERRUPT = 32'b0;
		else INTERRUPT = next_Interrupt;
	end
	
	always@(S_sel, S_wr, S_address, S_din, INTERRUPT, S_address, state)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_Interrupt = 32'b0;			// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address[3:0] == 4'b0010)
			next_Interrupt = S_din;			// offset 0x2
		else
			next_Interrupt = INTERRUPT;
	end
	
// SOURCE ADDRESS Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) sc_addr = 32'b0;
		else sc_addr = next_sc_addr;
	end

	always@(S_sel, S_wr, S_address , S_din, sc_addr, state)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_sc_addr = 32'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address[3:0] == 4'b0011)
			next_sc_addr = S_din;		// offset 0x3
		else
			next_sc_addr = sc_addr;
	end
	
// DESTINATION ADDRESS Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) ds_addr = 32'b0;
		else ds_addr = next_ds_addr;
	end
	
	always@(S_sel, S_wr, S_address, S_din, ds_addr, state)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_ds_addr = 32'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address[3:0] == 4'b0100)
			next_ds_addr = S_din;		// offset 0x4
		else
			next_ds_addr = ds_addr;
	end
	
// PUSH DESCRIPTOR Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) wr_en = 1'b0;
		else wr_en = next_wr_en;
	end
	
	always@(S_sel, S_wr, S_address, S_din, state)
	begin
		if( S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_wr_en = 1'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address [3:0] == 4'b0101 && S_din[0] == 1'b1)
			next_wr_en = 1'b1;		// offset 0x5
		else
			next_wr_en = 1'b0;
	end

// DESCRIPTOR SIZE Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) DATA_COUNT = 32'b0;
		else DATA_COUNT = next_data_count;
	end
	
	always@(S_sel, S_wr, data_count, DATA_COUNT, state, S_din, S_address)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_data_count = 32'b0;		// when op_clear
		else if(S_sel==1'b1 && S_wr == 1'b0 /*&& S_address[3:0] == 4'b0110*/)
			next_data_count = {28'b0, data_count};
		else
			next_data_count = DATA_COUNT;
	end

// DATA SIZE Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) data_size = 32'b0;
		else data_size = next_data_size;
	end
	
	always@(S_sel, S_wr, S_address, S_din, data_size, state)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_data_size = 32'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address[3:0] == 4'b0111)
			next_data_size = S_din;		// offset 0x7
		else
			next_data_size = data_size;
	end

// OPERATION MODE Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) opmode =32'b0;
		else opmode = next_opmode;
	end
	
	always@(S_sel, S_wr, S_address, S_din, opmode, state)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b1 && S_din[0] == 1'b1 && S_address[3:0] == 4'b0000 && state == DONE)
			next_opmode = 32'b0;		// when op_clear
		else if(S_sel == 1'b1 && S_wr == 1'b1 && S_address[3:0] == 4'b1000)
			next_opmode = S_din;		// offset 0x8
		else
			next_opmode = opmode;
	end
	
// OPERATION DONE Register
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) OP_DONE = 32'b0;
		else	OP_DONE = {31'b0, op_done};
	end

/////////////////////////////////////////////////////////
	always@(posedge clk or negedge reset_n)		// whenever clock is rising edge or reset is falling edge
	begin
		if(reset_n == 0) S_dout = 32'b0;
		else S_dout = next_S_dout;
	end
	
	
	always@(S_sel, S_wr, S_address, Interrupt, sc_addr, ds_addr, data_size, DATA_COUNT, opmode, OP_DONE)
	begin
		if(S_sel == 1'b1 && S_wr == 1'b0)
		begin
			if(S_address[3:0] == 4'b0010) next_S_dout = {31'b0, Interrupt};
			else if(S_address[3:0] == 4'b0011) next_S_dout = sc_addr;
			else if(S_address[3:0] == 4'b0100) next_S_dout = ds_addr;
			else if(S_address[3:0] == 4'b0110) next_S_dout = DATA_COUNT;	// DESCRIPTOR SIZE 
			else if(S_address[3:0] == 4'b0111) next_S_dout = data_size;
			else if(S_address[3:0] == 4'b1000) next_S_dout = opmode;
			else if(S_address[3:0] == 4'b1001) next_S_dout = OP_DONE;
			else										  next_S_dout = 32'b0;
		end
		else
			next_S_dout = 32'b0;
	end

endmodule
