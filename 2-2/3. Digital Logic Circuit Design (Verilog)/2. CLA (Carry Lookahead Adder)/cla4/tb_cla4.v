`timescale 1ns/100ps

module tb_cla4;
	reg [3:0] tb_a, tb_b;	// 4bits 2 input
	reg tb_ci;					// 1bit 1 input
	wire [3:0] tb_s;			// 4bits output
	wire tb_co;					// 1bit output
	
	wire [4:0] tb_result;	// 5bits output
	
	assign tb_result = {tb_co, tb_s};
	
	cla4 U0_cla4(.a(tb_a), .b(tb_b), .ci(tb_ci), .s(tb_s), .co(tb_co)); //express by instance
	
	initial
	begin
		tb_a=0; tb_b=0; tb_ci=0;						//at first, input(a,b,ci)=(0,0,0)
      #10; tb_a=4'h3; tb_b=4'h5; tb_ci=0;			//after 10ns, input(a,b,ci)=(3,5,0)
      #10; tb_a=4'h7; tb_b=4'h9; tb_ci=0;			//after 10ns, input(a,b,ci)=(7,9,0)
      #10; tb_a=4'h5; tb_b=4'h5; tb_ci=1;			//after 10ns, input(a,b,ci)=(5,5,1)
      #10; tb_a=4'h8; tb_b=4'h7; tb_ci=1;			//after 10ns, input(a,b,ci)=(8,7,1)
      #10; tb_a=4'hf; tb_b=4'hf; tb_ci=0;			//after 10ns, input(a,b,ci)=(16,16,0)
      #10; tb_a=4'hf; tb_b=4'hf; tb_ci=1;			//after 10ns, input(a,b,ci)=(16,16,1)
      #10; $stop;											//after 10ns, stop
		
	end
	
endmodule
