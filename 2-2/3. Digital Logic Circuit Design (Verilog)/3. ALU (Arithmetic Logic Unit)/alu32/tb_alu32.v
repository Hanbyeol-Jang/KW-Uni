`timescale 1ns/100ps

module tb_alu32(); 				//selfchecking testbench with testvectors
reg		clk,reset;									// input clk, reset
reg      [31:0]   tb_a,tb_b,y_expected;		// 32bits 3 inputs
reg      [2:0]      tb_op;							// 3 bits input tb_op
wire     [31:0]   tb_result;						// 32 bits output tb_result
wire            tb_c,tb_n,tb_z,tb_v;			// 4 outputs
reg		[31:0] vectornum,errors;				// 32bits input vectornum, errors
reg	[150:0] testvectors[10000:0];				

alu32 U0_alu32(.a(tb_a),.b(tb_b),.op(tb_op),.result(tb_result),.c(tb_c),.n(tb_n),.z(tb_z),.v(tb_v));  // ALU 32
	
always
begin
	clk = 1;#5;clk=0;#5;						// at first clk=1, after 5 ns, clk=0
end

initial
begin
		$readmemb("testvectors.tv",testvectors);	//read memo "testvectors.tv"
		vectornum=0; errors = 0;
		reset = 1; #27; reset = 0;			// at first reset =1 after 27ns rest 0
end

always @ (posedge clk)
begin
	#1; {tb_a,tb_b,tb_op,y_expected} = testvectors[vectornum];
end

always @ (negedge clk)	
begin
		if(~reset)
		begin
				if(tb_result !== y_expected)		// IS tb_result different with y_expected?
				begin
						$display("Error: A=%b, B=%b, Opcode=%b",tb_a,tb_b,tb_op);	//print error message
						$display("Expected output: %b",y_expected);
						$display("Output: %b",tb_result);
						errors = errors+1;
				end
		end
vectornum = vectornum +1;
if(testvectors[vectornum] === 151'bx)
		begin
			$display("%d tests completed with %d errors",vectornum,errors);	//print result
			#4;	$stop;
		end
end

endmodule
