module BUS_addr(address, S0_sel, S1_sel, S2_sel, S3_sel);		// bus addresss decoder
	input [7:0] address;									// 8 bits input
	output reg S0_sel, S1_sel, S2_sel, S3_sel;	// output reg
	
	wire [3:0] w_addr;
	
	assign w_addr = address[7:4];
	
	always@(w_addr)
	begin
		if(w_addr == 4'h0)											// if address 4bits = 0
			{S0_sel, S1_sel, S2_sel, S3_sel} = 4'b1000;
			
		else if(w_addr == 4'h1)										// if address 4bits = 1
			{S0_sel, S1_sel, S2_sel, S3_sel} = 4'b0100;
			
		else if(w_addr == 2 || w_addr == 3)						// if address 4bits = 2 or 3
			{S0_sel, S1_sel, S2_sel, S3_sel} = 4'b0010;
			
		else if(w_addr == 4 || w_addr == 5)						// if address 4bits = 4 or 5
			{S0_sel, S1_sel, S2_sel, S3_sel} = 4'b0001;
			
		else																// default
			{S0_sel, S1_sel, S2_sel, S3_sel} = 4'b0000;
	end
endmodule
