module rca_clk(clock, a, b, ci, s_rca, co_rca);
	input 			clock;		//input clock
	input  [31:0]  a, b;			//32bits 2 input
	input 			ci;			//carry in
	output [31:0]  s_rca;		//32bits sum(output)
	output 			co_rca;		//carry out
	
	reg [31:0] reg_a, reg_b;		//32bits 2 input
	reg 		  reg_ci;				//carry in
	reg [31:0] reg_s_rca;			//32bits sum(input)
	reg 		  reg_co_rca;			//carry out
	
	wire [31:0] wire_s_rca;			//32bits sum(output)
	wire 			wire_co_rca;		//carry out
	
	always @ (posedge clock)
	begin
	
		reg_a 		<= a;
		reg_b 		<= b;
		reg_ci 		<= ci;
		reg_s_rca   <= wire_s_rca;
		reg_co_rca	<= wire_co_rca;
		
	end
	
	rca32 U0_rca32(.a(reg_a), .b(reg_b), .ci(reg_ci), .s(wire_s_rca), .co(wire_co_rca));	//express by instance
	
	assign s_rca  = reg_s_rca;
	assign co_rca = reg_co_rca;
	
endmodule
