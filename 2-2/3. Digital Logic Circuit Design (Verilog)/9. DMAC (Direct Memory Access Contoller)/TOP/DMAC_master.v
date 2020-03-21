module DMAC_master(clk, reset_n, op_start, op_done, op_clear, M_req, M_grant, M_wr, M_address, M_dout, M_din, sc_addr, ds_addr, data_size, data_count, rd_en, state, opmode);
	input clk, reset_n;
	input M_grant, op_start, op_clear;
	input [31:0] sc_addr, ds_addr, data_size, M_din, opmode;
	input [3:0] data_count;
	output reg op_done, M_req, rd_en, M_wr;
	output reg [2:0] state;
	output reg [7:0] M_address;
	output reg [31:0] M_dout;
	reg [31:0] next_data_size, next_sc_addr, next_ds_addr;
	reg [2:0] next_state;
	reg [31:0] SC_ADDR, DS_ADDR, DATA_SIZE;
	
	parameter IDLE    = 3'b000;
	parameter POP     = 3'b001;
	parameter REQUEST = 3'b010;
	parameter READ    = 3'b011;
	parameter WRITE   = 3'b100;
	parameter DONE    = 3'b101;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) state = IDLE;
		else				  state = next_state;
	end
	
	always@(op_start, next_data_size, data_count, M_grant, op_clear, state)
	begin
		case(state)
		IDLE:
			begin
				if(op_start == 1'b1) next_state = POP;
				else						next_state = IDLE;
			end
		POP:
			begin
				if(next_data_size[7:0] != 8'b0) next_state = REQUEST;
				else if(next_data_size[7:0] == 8'b0)
					begin
						if(data_count == 4'b0) next_state = DONE;
						else next_state = 3'bx;
					end
				else  next_state = 3'bx;
			end
		REQUEST:
			begin
				if(M_grant == 1'b1) next_state = READ;
				else next_state = REQUEST;
			end
		READ:
			begin
				next_state = WRITE;
			end
		WRITE:
			begin
				if(next_data_size[7:0] != 8'b0) next_state = READ;
				else if(next_data_size[7:0] == 8'b0)
					begin
						if(data_count > 4'b0) next_state = POP;
						else next_state = DONE;
					end
				else next_state = 3'bx;
			end
		DONE:
			begin
				if(op_clear == 1'b1) next_state = IDLE;
				else next_state = DONE;
			end
		default : next_state = 3'bx;
				
		endcase
	end
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0)
			begin
				SC_ADDR = 32'b0; DS_ADDR = 32'b0; DATA_SIZE = 32'b0;
			end
		else
			begin
				SC_ADDR = next_sc_addr; DS_ADDR = next_ds_addr; DATA_SIZE = next_data_size;
			end
	end

	always@(state, sc_addr, SC_ADDR, opmode, ds_addr, data_size, DS_ADDR, DATA_SIZE, M_din)
	begin
		case(state)
			IDLE:
				begin
					next_sc_addr = 32'b0; next_ds_addr = 32'b0; next_data_size = 32'b0; M_req = 1'b0; M_address = 8'b0; M_wr = 1'b0; M_dout = 32'b0; op_done = 1'b0;
				end
			POP:
				begin
					next_sc_addr = sc_addr; next_ds_addr = ds_addr; next_data_size = data_size; M_req = 1'b0; M_address = 8'b0; M_wr = 1'b0; M_dout = 32'b0; op_done = 1'b0;
				end
			REQUEST:
				begin
					next_sc_addr = SC_ADDR; next_ds_addr = DS_ADDR; next_data_size = DATA_SIZE; M_req = 1'b1; M_address = 8'b0; M_wr = 1'b0; M_dout = 32'b0; op_done = 1'b0;
				end
			READ:
				begin
					next_sc_addr = SC_ADDR; next_ds_addr = DS_ADDR; next_data_size = DATA_SIZE - 1; M_req = 1'b1; M_address = SC_ADDR[7:0]; M_wr = 1'b0; M_dout = 32'b0; op_done = 1'b0;
				end
			WRITE:
				begin
					next_sc_addr = SC_ADDR + opmode[0];	next_ds_addr = DS_ADDR + opmode[1]; next_data_size = DATA_SIZE; M_req = 1'b1; M_address = DS_ADDR[7:0]; M_wr = 1'b1; M_dout = M_din; op_done = 1'b0;
				end
			DONE:
				begin
					next_sc_addr = 32'b0; next_ds_addr = 32'b0; next_data_size = 32'b0; M_req = 1'b0; M_address = 8'b0; M_wr = 1'b0; M_dout = 32'b0; op_done = 1'b1;
				end
			default:
				begin
					next_sc_addr = 32'bx; next_ds_addr = 32'bx; next_data_size = 32'bx; M_req = 1'bx; M_address = 8'bx; M_wr = 1'bx; M_dout = 32'bx; op_done = 1'bx;
				end
		endcase	
	end
	
	always@(next_state)
	begin
		case(next_state)	
			IDLE     : rd_en = 1'b0;
			POP      : rd_en = 1'b1;
			REQUEST  : rd_en = 1'b0;
			READ     : rd_en = 1'b0;
			WRITE 	: rd_en = 1'b0;
			DONE     : rd_en = 1'b0;
			default : rd_en = 1'bx;
		endcase
	end
	
endmodule
