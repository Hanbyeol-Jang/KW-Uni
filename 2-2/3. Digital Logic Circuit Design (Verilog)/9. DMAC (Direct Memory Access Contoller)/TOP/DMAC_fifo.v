module DMAC_fifo(clk, reset_n, rd_en, wr_en, din0, din1, din2, dout0, dout1, dout2, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err);
	input clk, reset_n, rd_en, wr_en;			// clock, reset, read, write enable
	input [31:0] din0, din1, din2;				// 32bits source address, destination address, data size
	output [31:0] dout0, dout1, dout2;			
	output full, empty;
	output wr_ack, wr_err, rd_ack, rd_err;		
	output [3:0] data_count;						// data count 
	
	wire [2:0] head, next_head;					// wire
	wire [2:0] tail, next_tail;
	wire [2:0] state, next_state;
	wire [3:0] next_data_count;
	wire		  we, re;
	wire [31:0] to_mux0, to_mux1, to_mux2, to_ff0, to_ff1, to_ff2;
	
	// instance by using each modules
	_dff_3_r U0_head(.clk(clk), .reset_n(reset_n), .d(next_head), .q(head));
	_dff_3_r U1_tail(.clk(clk), .reset_n(reset_n), .d(next_tail), .q(tail));
	_dff_3_r U2_state(.clk(clk), .reset_n(reset_n), .d(next_state), .q(state));
	
	fifo_ns  U3_ns(.rd_en(rd_en), .wr_en(wr_en), .state(state), .data_count(data_count), .next_state(next_state));
	fifo_cal U4_cal(.state(next_state), .data_count(data_count), .head(head), .tail(tail), .re(re), .we(we), .next_data_count(next_data_count), .next_head(next_head), .next_tail(next_tail));
	_dff_4_r U5_data_count(.clk(clk), .reset_n(reset_n), .d(next_data_count), .q(data_count));
	fifo_out U6_fifo_out(.state(state), .data_count(data_count), .empty(empty), .full(full), .rd_ack(rd_ack), .rd_err(rd_err), .wr_ack(wr_ack), .wr_err(wr_err));
	
	Register_file U7_register(.clk(clk), .reset_n(reset_n), .wAddr(tail), .wData(din0), .we(we), .rAddr(head), .rData(to_mux0));
	Register_file U8_register(.clk(clk), .reset_n(reset_n), .wAddr(tail), .wData(din1), .we(we), .rAddr(head), .rData(to_mux1));
	Register_file U9_register(.clk(clk), .reset_n(reset_n), .wAddr(tail), .wData(din2), .we(we), .rAddr(head), .rData(to_mux2));
	
	mx2_to_ff U10_mx2(.d0(32'h0), .d1(to_mux0), .s(re), .y(to_ff0));
	mx2_to_ff U11_mx2(.d0(32'h0), .d1(to_mux1), .s(re), .y(to_ff1));
	mx2_to_ff U12_mx2(.d0(32'h0), .d1(to_mux2), .s(re), .y(to_ff2));
	
	_DFF31 U13_dff(.clk(clk), .reset_n(reset_n), .d(to_ff0), .q(dout0));
	_DFF31 U14_dff(.clk(clk), .reset_n(reset_n), .d(to_ff1), .q(dout1));
	_DFF31 U15_dff(.clk(clk), .reset_n(reset_n), .d(to_ff2), .q(dout2));

endmodule

module _dff_3_r(clk, reset_n, d, q);	// 3bits resettable flip flop
	input clk, reset_n;	// clock, reset
	input [2:0]	d;
	output reg [2:0] q;		

	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset is falling edge
	begin
		if(reset_n == 0)	q <= 1'b0;	
		else 					q <= d;					
	end
	
endmodule

module _dff_4_r(clk, reset_n, d, q); // 4bit resettable flip flop
	input clk, reset_n;		// clock, reset
	input [3:0]	d;
	output reg [3:0] q;		

	always @ (posedge clk or negedge reset_n)			// whenever clk is rising edge or reset is falling edge
	begin
		if(reset_n == 0)	q <= 1'b0;						
		else 					q <= d;	
	end
	
endmodule

module _DFF31(clk, reset_n, d, q);		// resettable 32bit flip flop
	input	clk, reset_n;			// input
	input [31:0] d;
	output reg [31:0] q;			// output reg
	
	always@(posedge clk or negedge reset_n)		// whenever clk is rising edge or reset is falling edge
	begin	
		if(reset_n==0) q<=32'b0;	
		else q<=d;					
	end	
	
endmodule

module fifo_ns(rd_en, wr_en, state, data_count, next_state);   // fifo_ns logic
	input rd_en, wr_en;								// input
	input [2:0] state;
	input [3:0] data_count;							// 8 bits data count
	output reg [2:0] next_state;			
	
	parameter IDLE 	 = 3'b000;			// define IDLE
	parameter WRITE 	 = 3'b001;			// define WRITE
	parameter READ 	 = 3'b010;			// define READ
	parameter WR_ERROR = 3'b011;			// define WR_ERROR
	parameter RD_ERROR = 3'b100;			// define RD_ERROR
	
	always@(state or wr_en or rd_en or data_count)
	begin
		case(state)	
			IDLE : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when IDLE
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else if (wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			READ : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when READ
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else if(wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			RD_ERROR : if(wr_en==0 && rd_en==0) next_state <= IDLE; // when RD_ERROR
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			WR_ERROR : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when WR_ERROR
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else	next_state <= 3'bxxx;
					 
			WRITE : if(wr_en==0 && rd_en==0) next_state <= IDLE;		// when WRITE
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else	next_state <= 3'bxxx;
					 
			default : next_state <= 3'bx;										// when default, unknown
		endcase
	end
endmodule

module fifo_cal(state, data_count, head, tail, re, we, next_data_count, next_head, next_tail);	//fifo_cal
	input [2:0] state, head, tail;					// input
	input [3:0] data_count;
	output reg re,we;										// output reg
	output reg [3:0] next_data_count;
	output reg [2:0] next_head, next_tail;
	
	parameter IDLE 	 = 3'b000;						// define
	parameter WRITE 	 = 3'b001;
	parameter READ 	 = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter RD_ERROR = 3'b100;

	always@(state, head, tail, data_count, we, re)
		begin
			case(state)			
			IDLE :														// when IDLE
				begin
					next_tail <= tail;
					next_head <= head;
					next_data_count <= data_count;
					we <= 1'b0;											// Initialization
					re <= 1'b0;
				end
			WRITE : 														// when WRITE
				begin
					next_tail <= tail + 3'b001;	
					next_head <= head;
					next_data_count <= data_count + 4'b0001;
					we <= 1'b1;											// Initialization
					re <= 1'b0;
				end
			READ : 														// when READ
				begin
					next_tail <= tail;	
					next_head <= head + 3'b001;
					next_data_count <= data_count - 4'b0001;	
					re <= 1'b1;											// Initialization
					we <= 1'b0;
				end	
			default : 													// when default
				begin
					next_tail <= tail;						
					next_head <= head;
					next_data_count <= data_count;
					re <= 1'b0;											// Initialization
					we <= 1'b0;
				end
			endcase
		end
endmodule		
			
module fifo_out(state, data_count, empty, full, rd_ack, rd_err, wr_ack, wr_err);	//fifo_out
	input [2:0] state;															// input
	input [3:0] data_count;
	output reg empty, full, rd_ack, rd_err, wr_ack, wr_err;			// output reg

	parameter IDLE 	 = 3'b000;		// define
	parameter WRITE 	 = 3'b001;
	parameter READ 	 = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter RD_ERROR = 3'b100;
	
	always @ (data_count)					// depend on data_count
	begin
		if(data_count==0)							// data=0, empty
			begin
				full<=0; empty<=1;
			end
		else if(data_count==4'b1000)			// data=8, full
			begin
				full<=1; empty<=0;
			end
		else
			begin										// otherwise, full =0, empty=0
				full<=0; empty<=0;
			end
	end
	
	always @ (state)							// depend on state
	begin
		case(state)
			IDLE : 																	// when IDLE
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=0; rd_err<=0;
				end
			WRITE : 																	// when WRITE
				begin
					wr_ack<=1; wr_err<=0; rd_ack<=0; rd_err<=0;
				end
			READ : 																	// when READ
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=1; rd_err<=0;
				end
			WR_ERROR : 																// when WR_ERROR
				begin
					wr_ack<=0; wr_err<=1; rd_ack<=0; rd_err<=0;
				end
			RD_ERROR : 																// when RD_ERROR
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=0; rd_err<=1;
				end
			default : 																// when default, unknown
				begin
					wr_ack<=1'bx; wr_err<=1'bx; rd_ack<=1'bx; rd_err<=1'bx;
				end
		endcase
	end
endmodule

module Register_file(clk, reset_n, wAddr, wData, we, rAddr, rData);		// register_file
	input clk, reset_n, we;				// input
	input [2:0] wAddr, rAddr;			// address
	input [31:0] wData;
	output [31:0] rData;					// output
	
	wire[7:0]to_reg;						// wire
	wire[31:0]from_reg[7:0];	
	
	// instance by using each modules
	register32_8 U0_register32_8(.clk(clk), .reset_n(reset_n), .en(to_reg), .d_in(wData), .d_out0(from_reg[0]), .d_out1(from_reg[1]), .d_out2(from_reg[2]), .d_out3(from_reg[3]), .d_out4(from_reg[4]), .d_out5(from_reg[5]), .d_out6(from_reg[6]), .d_out7(from_reg[7]));
	write_operation U1_write_operation(.Addr(wAddr), .we(we), .to_reg(to_reg));
	read_operation U2_read_operation(.Addr(rAddr), .Data(rData), .from_reg0(from_reg[0]), .from_reg1(from_reg[1]), .from_reg2(from_reg[2]), .from_reg3(from_reg[3]), .from_reg4(from_reg[4]), .from_reg5(from_reg[5]), .from_reg6(from_reg[6]), .from_reg7(from_reg[7]));
	
endmodule

module register32_8(clk, reset_n, en, d_in, d_out0, d_out1, d_out2, d_out3, d_out4, d_out5, d_out6, d_out7);		// register32_8
	input clk, reset_n;				// input
	input  [7:0]  en;																																
	input  [31:0] d_in;
	output [31:0] d_out0, d_out1, d_out2, d_out3, d_out4, d_out5, d_out6, d_out7;		// output
	
	// instance by using 8 register32_r_en
	register32_r_en U0_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out0), .en(en[0]));
	register32_r_en U1_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out1), .en(en[1]));
	register32_r_en U2_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out2), .en(en[2]));
	register32_r_en U3_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out3), .en(en[3]));
	register32_r_en U4_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out4), .en(en[4]));
	register32_r_en U5_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out5), .en(en[5]));
	register32_r_en U6_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out6), .en(en[6]));
	register32_r_en U7_register32_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in), .d_out(d_out7), .en(en[7]));
	
endmodule

module register32_r_en(clk, reset_n, d_in, d_out, en);		// 32bits register reset,enable
	input clk, reset_n, en;			// input
	input  [31:0] d_in;													
	output [31:0] d_out;				// output
	
	// instance by using 4 register8_r_en
	register8_r_en U0_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[7:0]),   .d_out(d_out[7:0]),   .en(en));	
	register8_r_en U1_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[15:8]),  .d_out(d_out[15:8]),  .en(en));
	register8_r_en U2_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[23:16]), .d_out(d_out[23:16]), .en(en));
	register8_r_en U3_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[31:24]), .d_out(d_out[31:24]), .en(en));
	
endmodule

module register8_r_en(clk, reset_n, d_in, d_out, en);			// register8_r_en
	input clk, reset_n, en;				// input
	input [7:0] d_in;					
	output [7:0] d_out;					// output
	
	// instance by using 8 _dff_r_en
	_dff_r_en U0_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[0]), .q(d_out[0]));
	_dff_r_en U1_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[1]), .q(d_out[1]));
	_dff_r_en U2_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[2]), .q(d_out[2]));
	_dff_r_en U3_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[3]), .q(d_out[3]));
	_dff_r_en U4_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[4]), .q(d_out[4]));
	_dff_r_en U5_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[5]), .q(d_out[5]));
	_dff_r_en U6_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[6]), .q(d_out[6]));
	_dff_r_en U7_dff_r_en(.clk(clk), .reset_n(reset_n), .en(en), .d(d_in[7]), .q(d_out[7]));
	
endmodule

module _dff_r_en(clk, reset_n, en, d, q);				// reset, enable d flip flop
	input clk,reset_n, en, d;			// input
	output reg q;							// output
	
	always@(posedge clk or negedge reset_n) begin	// whenever clock is rising edge or reset is falling edge
		if(~reset_n)	q<=1'b0;			
		else if(en)		q<=d;									
		else				q<=q;		
	end
endmodule

module write_operation(Addr, we, to_reg);				// write operation
	input we;							// input
	input [2:0]Addr;
	output [7:0]to_reg;				// output
	
	wire[7:0] write_wire;			// wire
	
	// instance by using each modules
	_3_to_8_decoder U0_3_to_8_decoder(.d(Addr), .q(write_wire));
	_and2 U1_and2(.a(we), .b(write_wire[0]), .y(to_reg[0]));
	_and2 U2_and2(.a(we), .b(write_wire[1]), .y(to_reg[1]));
	_and2 U3_and2(.a(we), .b(write_wire[2]), .y(to_reg[2]));
	_and2 U4_and2(.a(we), .b(write_wire[3]), .y(to_reg[3]));
	_and2 U5_and2(.a(we), .b(write_wire[4]), .y(to_reg[4]));
	_and2 U6_and2(.a(we), .b(write_wire[5]), .y(to_reg[5]));
	_and2 U7_and2(.a(we), .b(write_wire[6]), .y(to_reg[6]));
	_and2 U8_and2(.a(we), .b(write_wire[7]), .y(to_reg[7]));
	
endmodule

module _3_to_8_decoder(d, q);				//3_to_8_decoder
	input 	  [2:0] d;			// input
	output reg [7:0] q;			// output reg
	
	always@(d) begin							
		case(d)		
			3'b000: q=8'b00000001;			// one-hot encoding
			3'b001: q=8'b00000010;
			3'b010: q=8'b00000100;
			3'b011: q=8'b00001000;
			3'b100: q=8'b00010000;
			3'b101: q=8'b00100000;
			3'b110: q=8'b01000000;
			3'b111: q=8'b10000000;
			default: q=8'hx;					// when default, unknown
		endcase
	end
endmodule

module read_operation(Addr, Data, from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7);  // read_operation
	input  [31:0] from_reg0, from_reg1, from_reg2, from_reg3, from_reg4, from_reg5, from_reg6, from_reg7;				// input
	input  [2:0]  Addr;
	output [31:0] Data;																															// output
	
	_8_to_1_MUX U0_8_to_1_MUX(.a(from_reg0), .b(from_reg1), .c(from_reg2), .d(from_reg3), .e(from_reg4), .f(from_reg5), .g(from_reg6), .h(from_reg7), .sel(Addr), .d_out(Data));
	
endmodule

module _8_to_1_MUX(a, b, c, d, e, f, g, h, sel, d_out);	// _8_to_1 mux
	input [31:0] a, b, c, d, e, f, g, h;			// input
	input [2:0]	sel;
	output reg[31:0]d_out;								// output reg
	
	always@(sel, a, b, c, d, e, f, g, h)begin
		case(sel)											// depend on sel
			3'b000: d_out=a;			
			3'b001: d_out=b;
			3'b010: d_out=c;
			3'b011: d_out=d;
			3'b100: d_out=e;
			3'b101: d_out=f;
			3'b110: d_out=g;
			3'b111: d_out=h;
			default:d_out=32'hx;							// when default, unknown
		endcase
	end
endmodule

module mx2_to_ff(d0,d1,s,y);	//32bits mx
input    [31:0] d0,d1;	// 32bits input d0,d1
input 			 s;		// input 
output   [31:0] y;		// 32bits output


assign y=(s==1'b0) ? d0 : d1;  //if s = 0, y=d0, else, y=d1

endmodule

