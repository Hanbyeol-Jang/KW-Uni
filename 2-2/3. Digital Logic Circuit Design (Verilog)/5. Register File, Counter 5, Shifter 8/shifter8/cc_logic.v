module cc_logic(op, shamt, d_in, d_out, do_next);	//cc logic
	input  [2:0]	op;			// 3bits input op
	input  [1:0]	shamt;		// 2bits input shamt
	input  [7:0]	d_in;			// 8bits input d_in
	input  [7:0]	d_out;		// 8bits input d_out
	output [7:0]	do_next;		// 8bits output do_next
	reg 	 [7:0]	do_next;		// 8bits reg do_next
	
	wire 	 [7:0]	d_lsl;		// 8bits wire d_lsl
	wire	 [7:0]   d_lsr;		// 8bits wire d_lsr
	wire   [7:0]	d_asr;		// 8bits wire d_asr
	
	parameter NOP 	= 3'b000;		// define NOP  = 000
	parameter LOAD = 3'b001;		// define LOAD = 001
	parameter LSL 	= 3'b010;		// define LSL  = 010
	parameter LSR 	= 3'b011;		// define LSR  = 011
	parameter ASR 	= 3'b100;		// define ASR  = 100
	
	always @ (op, shamt, d_in, d_out, d_lsl, d_lsr, d_asr)
	begin
		case(op)					
		NOP 	: do_next <= d_out; 	// when NOP,  do_next = d_out
		LOAD 	: do_next <= d_in;	// when LOAD, do_next = d_in
		LSL 	: do_next <= d_lsl;	// when LSL,  do_next = d_lsl
		LSR 	: do_next <= d_lsr;	// when LSR,  do_next = d_lsr
		ASR 	: do_next <= d_asr;	// when ASR,  do_next = d_asr
		default : do_next <= 8'bx;	// when default, do_next = unknown
		
		endcase
	end
	
	LSL8 U0_LSL8(.d_in(d_out), .shamt(shamt), .d_out(d_lsl));		// instance by using LSL8, LSR8 and ASR8
	LSR8 U1_LSR8(.d_in(d_out), .shamt(shamt), .d_out(d_lsr));
	ASR8 U2_ASR8(.d_in(d_out), .shamt(shamt), .d_out(d_asr));
	
endmodule

	
		
		