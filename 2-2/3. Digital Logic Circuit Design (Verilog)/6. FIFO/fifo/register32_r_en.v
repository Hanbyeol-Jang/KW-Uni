module register32_r_en(clk, reset_n, d_in, d_out, en);		//32bits register reset,enable
	input clk, reset_n, en;		// 3 inputs
	input  [31:0] d_in;			// 32bits input d_in
	output [31:0] d_out;			// 32bits output d_out
	
	register8_r_en U0_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[7:0]),   .d_out(d_out[7:0]),   .en(en));		// instance by using 4register8_r_en
	register8_r_en U1_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[15:8]),  .d_out(d_out[15:8]),  .en(en));
	register8_r_en U2_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[23:16]), .d_out(d_out[23:16]), .en(en));
	register8_r_en U3_register_r_en(.clk(clk), .reset_n(reset_n), .d_in(d_in[31:24]), .d_out(d_out[31:24]), .en(en));
	
endmodule
