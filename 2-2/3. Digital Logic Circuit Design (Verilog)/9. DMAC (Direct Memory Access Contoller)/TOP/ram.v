module ram(clk, cen, wen, addr, din, dout);
	input clk;						// clock
	input cen, wen;				// chip enable, write enable
	input [4:0] addr;				// 5bits address
	input [31:0] din;				// 32bits data in
	
	output reg [31:0] dout;		// 32bits data out
	
	reg [31:0] mem [0:31];		// variable memory area
	
	integer i;
	
	initial begin									// initailization memory
	 for(i=0; i<32; i=i+1)
		mem [i] = 32'b0;							// 0
	end
	
	always@(posedge clk)							// whenever clk is rising edge
	begin
		if(cen==1'b1&&wen==1'b1) 				// if cen = 1 & wen = 1 
		begin
			mem[addr] <= din;						// input din into memory
			dout <= 32'b0;							// dout = 0
		end
		else if(cen==1'b1&&wen==1'b0)			// if cen = 1& wen = 0
			dout <= mem[addr];					// output dout from memory 
		else if(cen==1'b0)						// if cen = 0
			dout <= 32'b0;							// dout = 0
		else											// otherwise,
			begin
				mem[addr] <= 32'bx;				// unknown
				dout <= 32'bx;
			end
		end
endmodule
	