`timescale 1ns/100ps		
module tb_fifo;		
	reg tb_clk, tb_reset_n, tb_rd_en, tb_wr_en;		// 4 reg
	reg [31:0] tb_din;										// 32bits reg
	wire [31:0] tb_dout;										// 32bits wire
	wire [3:0] tb_data_count;								// 4bits wire
	wire tb_full, tb_empty, tb_wr_ack, tb_wr_err, tb_rd_ack, tb_rd_err;	// 6 wire
	
	fifo U0_fifo(.clk(tb_clk), .reset_n(tb_reset_n), .rd_en(tb_rd_en), .wr_en(tb_wr_en),			// instance by using fifo
	.din(tb_din), .dout(tb_dout), .data_count(tb_data_count), .full(tb_full), .empty(tb_empty),
	.wr_ack(tb_wr_ack), .wr_err(tb_wr_err), .rd_ack(tb_rd_ack), .rd_err(tb_rd_err));

	always
	begin
		tb_clk=0; #5; tb_clk=1; #5;		// every 5ns, invert clk
	end
	
	initial
	begin
		tb_reset_n=0; tb_din=32'h0; tb_rd_en=0; tb_wr_en=0; #10;	// (tb_reset_n,tb_din,tb_rd_en,tb_wr_en)=(0,0,0,0)
		tb_reset_n=1; #10;													// after 10ns, rb_reset_b=1					
		tb_rd_en=1; #10;														// after 10ns, tb_rd_en=1
		tb_rd_en=0; tb_wr_en=1; tb_din=32'hffff0000; #10;			// after 10ns, (tb_rd_en,tb_wr_en,tb_din)=(0,1,ffff0000)
		tb_din=32'h0000ffff; #10;											// after 10ns, tb_din=0000ffff
		tb_wr_en=1; tb_din=32'h00ff00ff; #10;							// after 10ns, tb_wr_en=1, tb_din=00ff00ff
		tb_wr_en=1; tb_din=32'h000fff00; #10;							// after 10ns, tb_wr_en=1, tb_din=000fff00
		tb_din=32'hff0ff000; #10;											// after 10ns, tb_din=ff0ff000
		tb_rd_en=1; tb_wr_en=0; #10;										// after 10ns, tb_rd_en=1,tb_wr_en=0
		tb_rd_en=0; tb_wr_en=1; tb_din=32'hf0f0f0f0; #10;			// after 10ns, tb_re_en=0,tb_wr_en=1,tb_din=f0f0f0f0
		tb_din=32'hffffffff; #10;											// after 10ns, tb_din=ffffffff
		tb_din=32'h0000ff00; #10;											// after 10ns, tb_din=0000ff00
		tb_din=32'hffffff00; #10;											// after 10ns, tb_din=ffffff00
		tb_din=32'h00ffffff; #10;											// after 10ns, tb_din=00ffffff
		tb_din=32'hff0000ff; #10;											// after 10ns, tb_din=ff0000ff
		tb_wr_en=0; #10;														// after 10ns, tb_wr_en=0
		tb_rd_en=1; tb_wr_en=0; #10;										// after 10ns, tb_rd_en=1,tb_wr_en=0
		tb_rd_en=1; #50;														// after 10ns, tb_rd_en=1
		tb_rd_en=0; tb_wr_en=1; tb_din=32'hfff0f000; #10;			// after 50ns, tb_rd_en=0,tb_wr_en=1,tb_din=fff0f000
		tb_rd_en=1; tb_wr_en=0; #50;										// after 10ns, tb_rd_en=1,tb_wr_en=0
		tb_rd_en=1; #10;														// after 50ns, tb_rd_en=1
		tb_wr_en=1; tb_rd_en=0; tb_din=32'h00ffff00; #10;			// after 10ns, tb_wr_en=1,tb_rd_en=0,tb_din=00ffff00
		tb_reset_n=0; #10;													// after 10ns, tb_reset_n=0
		$stop;																	// after 10ns, stop
	end
	
endmodule