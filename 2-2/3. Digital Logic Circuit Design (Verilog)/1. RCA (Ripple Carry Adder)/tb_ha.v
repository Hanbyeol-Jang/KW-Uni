`timescale 1ns/100ps		//set time

module tb_ha;
	reg tb_a,tb_b;			//input a,b
	wire tb_s,tb_co;		//output sum, carry out
	
	ha U0_ha(.a(tb_a),.b(tb_b),.s(tb_s),.co(tb_co));		//ha instance
	
	initial
	begin
		tb_a=0; tb_b=0;			//initializing
		#10; tb_a=0; tb_b=1;		//1+0
		#10; tb_a=1; tb_b=0;		//0+1
		#10; tb_a=1; tb_b=1;		//1+1
		#10; $stop;					//stop
end
endmodule
