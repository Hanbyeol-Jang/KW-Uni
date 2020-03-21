module cla_clk(clock, a, b, ci, s_cla, co_cla);
	input clock;					//input clock
	input [31:0] a, b;			//32bits 2 input
	input ci;						//carry in
	output [31:0] s_cla;			//32bits sum(output)
	output co_cla;					//carry out
	
	reg [31:0] reg_a, reg_b;	//32bits 2 input
	reg 		  reg_ci;			//carry in
	reg [31:0] reg_s_cla;		//32bits sum (input)
	reg 		  reg_co_cla;		//carry out
	
	wire [31:0] wire_s_cla;		//32bits sum(output)
	wire			wire_co_cla;	//carry out
	
	always @ (posedge clock)
	begin
		
		reg_a 		<= a;
		reg_b 		<= b;
		reg_ci 		<= ci;
		reg_s_cla 	<= wire_s_cla;
		reg_co_cla  <= wire_co_cla;
	
	end
	
	cla32 U0_cla32(.a(reg_a), .b(reg_b), .ci(reg_ci), .s(wire_s_cla), .co(wire_co_cla));	//express by instance
						
	assign s_cla  = reg_s_cla;
	assign co_cla = reg_co_cla;
	
endmodule
