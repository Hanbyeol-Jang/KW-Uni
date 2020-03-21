module memory (clk, cen, wen, addr, din,dout);
	input clk;						// clock
	input cen, wen;				// chip enable, write enable
	input [4:0] addr;				// address
	input [31:0] din;				// data in
	
	output reg [31:0] dout;		// data out
	
	reg [31:0] mem [0:31];
	
	integer i;
	
	initial begin										// initailization memory
	 for(i=0; i<32; i=i+1)
		mem [i] = 32'b0;								// 0
	end
	
	always@(posedge clk)								// when clk is rising edge
	begin
		if(cen==1'b1&&wen==1'b1) 					// if cen = 1 & wen = 1 
		begin
			mem[addr]<=din; dout<=32'b0;			// input, output dout = 0
		end
		else if(cen==1'b1&&wen==1'b0)				// if cen = 1& wen = 0
			dout<=mem[addr];							// output memory
		else
			dout<=32'b0;								// otherwise, output 0
	end
endmodule
	