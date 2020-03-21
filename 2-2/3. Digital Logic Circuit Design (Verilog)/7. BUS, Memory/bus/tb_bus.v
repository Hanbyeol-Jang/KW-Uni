`timescale 1ns/100ps	
	
module tb_bus;		
	reg clk, reset_n, tb_M0_req, tb_M1_req, tb_M0_wr, tb_M1_wr;			// 6 reg
	reg [7:0] tb_M0_address, tb_M1_address;									// 8bits 2 reg
	reg [31:0] tb_M0_dout, tb_M1_dout, tb_S0_dout, tb_S1_dout;			// 32bits 4 reg
	wire tb_M0_grant, tb_M1_grant, tb_S0_sel, tb_S1_sel, tb_S_wr;		// 5 wire		
	wire [7:0] tb_S_address;														// 8bits wire
	wire [31:0] tb_S_din, tb_M_din;												// 32bits 2 wire
	
	// instance by using bus
	bus U0_bus(.clk(clk), .reset_n(reset_n), .M0_req(tb_M0_req), .M1_req(tb_M1_req), .M0_wr(tb_M0_wr), .M1_wr(tb_M1_wr), 
			.M0_address(tb_M0_address), .M1_address(tb_M1_address), .M0_dout(tb_M0_dout), .M1_dout(tb_M1_dout),
			.S0_dout(tb_S0_dout), .S1_dout(tb_S1_dout), .M0_grant(tb_M0_grant), .M1_grant(tb_M1_grant), .M_din(tb_M_din),
			.S0_sel(tb_S0_sel), .S1_sel(tb_S1_sel), .S_wr(tb_S_wr), .S_address(tb_S_address), .S_din(tb_S_din));
			
	// values in bus module put testbench values by one to one
	always	
	begin
		clk=0; #5; clk=1; #5;		// every 5ns, invert clk
	end
	
	initial
	begin
		reset_n=0; tb_M0_req=0; tb_M1_req=0; tb_M0_wr=0; tb_M1_wr=0;			// initialization
		tb_M0_address=8'b0; tb_M1_address=8'b0; tb_M0_dout=32'b0; tb_M1_dout=32'b0;
		tb_S0_dout=32'b0; tb_S1_dout=32'b0; #10;		
		
		reset_n=1;tb_M0_req=1; tb_M0_wr=1; tb_M0_address=8'h01; tb_M0_dout=32'h11111111;	// then, every 10 ns, input values and check output
		tb_S0_dout=32'h01; tb_S1_dout=32'h02; #10;
		tb_M0_address=8'h10; tb_M0_dout=32'h22222222; #10;	
		tb_M0_address=8'h25; tb_M0_dout=32'h33333333; #10;
		tb_M0_address=8'h41; tb_M0_dout=32'h44444444; #10;	
		tb_M0_req=0; tb_M1_req=1; tb_M1_wr=1; #10;									// order from m1 grant
		tb_M1_address=8'h8; tb_M1_dout=32'h55555555; #10;	
		tb_M1_address=8'h21; tb_M1_dout=32'h66666666; #10;	
		tb_M0_req=1; tb_M1_req=0; #10;													// order from m0 grant
		tb_M0_address=8'h31; tb_M0_dout=32'h77777777; #10;
		tb_M0_address=8'h43; tb_M0_dout=32'h88888888; #10;
		tb_M0_req=0; tb_M1_req=1; tb_M1_address=8'h30; tb_M1_dout=32'h99999999; #10;	// otder from m1 grant
		$stop;
	end
	
endmodule
	