module bus_addr(address, s0_sel, s1_sel);		// bus addresss decoder
	input [7:0] address;								// 8 bits input
	output reg s0_sel, s1_sel;						// output reg
	
	always@(address)
		begin
			if( (address > 8'h00||address == 8'h00) && address<8'h20) {s0_sel,s1_sel}=2'b10;			// when address in right range, update s0_sel,s1_sel
			else if((address > 8'h20 || address == 8'h20)&& address<8'h3F) {s0_sel,s1_sel}=2'b01;
			else {s0_sel,s1_sel}=2'b00;
		end
		
endmodule
