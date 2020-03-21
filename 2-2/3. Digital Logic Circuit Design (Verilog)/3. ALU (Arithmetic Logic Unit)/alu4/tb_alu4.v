`timescale 1ns/100ps

module tb_alu4;						// testbench of ALU4
	reg	[3:0]	tb_a, tb_b;			// 4 bits 2 inputs
	reg 	[2:0] tb_op;				// 3 bits input tb_op
	wire	[3:0]	tb_result;			// 4 bits output tb_result
	wire			tb_c, tb_n, tb_z, tb_v;		// 4 outputs
	
	alu4 U0_alu4(.a(tb_a), .b(tb_b), .op(tb_op), .result(tb_result),
					 .c(tb_c), .n(tb_n), .z(tb_z), .v(tb_v));			
					 
	initial						// using self-checking testbench
	begin
	tb_a=4'b0000;		tb_b=4'b0000; tb_op=3'b000; 	#10;													//at first, input(a,b,c)=(0,0,0)
	if(tb_result!==~tb_a||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("000 failed");	
	tb_a=3'b1100;											   #10;
	if(tb_result!==~tb_a||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("000 failed");
						  tb_b=4'b0011;  	tb_op=3'b001;	#10;
	if(tb_result!==~tb_b||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("001 failed");
	tb_a=4'b0101;    tb_b=4'b1001;  tb_op=3'b010;	#10;
	if(tb_result!==4'b0001||tb_c!==0||tb_n!==0||tb_z!==0||tb_v!==0) $display ("010 failed");
	tb_a=4'b0101;    tb_b=4'b1010;  tb_op=3'b011;	#10;
	if(tb_result!==4'b1111||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("011 failed");
   tb_a=4'b0011;    tb_b=4'b0101;  tb_op=3'b100;	#10;
	if(tb_result!==4'b0110||tb_c!==0||tb_n!==0||tb_z!==0||tb_v!==0)   $display ("100 failed");
                                   tb_op=3'b101;	#10;
	if(tb_result!==4'b1001||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0)   $display ("101 failed");										  
   tb_a=4'b0000; 	  tb_b=4'b0000;  tb_op=3'b110;	#10;
	if(tb_result!==4'b0000||tb_c!==0||tb_n!==0||tb_z!==1||tb_v!==0) $display ("110 failed");
   tb_a=4'hf;       tb_b=4'hf;							#10;
	if(tb_result!==4'b1110||tb_c!==1||tb_n!==1||tb_z!==0||tb_v!==0) $display ("110 failed");
   tb_a=4'ha;       tb_b=4'h3;							#10;
	if(tb_result!==4'b1101||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("110 failed");
   tb_a=4'b0001;    tb_b=4'b1000;						#10;
	if(tb_result!==4'b1001||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("110 failed");
   tb_a=4'h7;       tb_b=4'h7;							#10;
	if(tb_result!==4'b1110||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==1) $display ("110 failed");
   tb_a=4'h3;       tb_b=4'h3;							#10;
	if(tb_result!==4'b0110||tb_c!==0||tb_n!==0||tb_z!==0||tb_v!==0) $display ("110 failed");
   tb_a=4'hf;       tb_b=4'h5;     tb_op=3'b111;	#10;
	if(tb_result!==4'b1010||tb_c!==1||tb_n!==1||tb_z!==0||tb_v!==0) $display ("111 failed");
   tb_a=4'h5;       tb_b=4'h7;							#10;
	if(tb_result!==4'b1110||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==0) $display ("111 failed");
   tb_a=4'ha;       tb_b=4'ha;							#10;
	if(tb_result!==4'b0000||tb_c!==1||tb_n!==0||tb_z!==1||tb_v!==0) $display ("111 failed");
   tb_a=4'h7;       tb_b=4'h9;							#10;
	if(tb_result!==4'b1110||tb_c!==0||tb_n!==1||tb_z!==0||tb_v!==1) $display ("111 failed");
	#10;	$stop;
	
	end
endmodule
