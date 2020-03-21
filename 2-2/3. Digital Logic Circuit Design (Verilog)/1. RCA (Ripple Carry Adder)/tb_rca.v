`timescale 1ns/100ps				//set time

module tb_rca;
	reg [3:0] tb_a,tb_b;			//4-bit input
	reg tb_ci;						//carry in
	wire [3:0] tb_s;				//4-bit sum
	wire tb_co;						//carry out
	wire [4:0] tb_result;		//5-bit result
	
	rca U0_rca(.a(tb_a),.b(tb_b),.ci(tb_ci),.s(tb_s),.co(tb_co));	//rca instance
	
	initial
	begin
		tb_a=4'b0; tb_b=4'b0; tb_ci=0;			//initializing
		#10; tb_a=3; tb_b=2;
		#10; tb_ci=1;
		
		#10; tb_ci=0; tb_a=1; tb_b=6;					
		#10; tb_ci=1;						
		#10; $stop;										//stop
end

assign tb_result={tb_co, tb_s};				//result 	
endmodule
