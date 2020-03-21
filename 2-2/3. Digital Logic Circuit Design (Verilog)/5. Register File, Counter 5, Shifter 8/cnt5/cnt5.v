module cnt5(cnt, clk, reset_n, inc);			//cnt5
	input			clk,reset_n, inc;					// 3 inputs
	output[2:0]	cnt;									// 3bits output cnt
	
	parameter zero  = 3'b000;	// define zero  = 000
	parameter one   = 3'b001;	// define one   = 001
	parameter two   = 3'b010;	// define tow   = 010
	parameter three = 3'b011;	// define three = 011
	parameter four  = 3'b100;	// define four  = 100

	reg [2:0]	cnt;				// 3bits reg cnt
	reg [2:0]	next_cnt;		// 3bits reg next_cnt
	
	always @ (posedge clk or negedge reset_n)		// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n == 1'b0)	cnt <= zero;			// if reset_n=0, cnt = zero
		else						cnt <= next_cnt;		// else cnt= next_cnt
	end	
	
	always @ (inc or cnt)	
	begin
		case({cnt,inc})
		{zero,1'b0}		:	next_cnt <=four;		//when cnt=0, if inc=0, next_cnt = four
		{zero,1'b1}		:	next_cnt <=one;		//when cnt=0, if inc=1, next_cnt = one
		{one,1'b0}		:	next_cnt <=zero;		//when cnt=1, if inc=0, next_cnt = zero
		{one,1'b1}		:	next_cnt <=two;		//when cnt=1, if inc=1, next_cnt = two
		{two,1'b0}		:	next_cnt <=one;		//when cnt=2, if inc=0, next_cnt = one
		{two,1'b1}		:	next_cnt <=three;		//when cnt=2, if inc=1, next_cnt = three
		{three,1'b0}	:	next_cnt <=two;		//when cnt=3, if inc=0, next_cnt = two
		{three,1'b1}	:	next_cnt <=four;		//when cnt=3, if inc=1, next_cnt = four
		{four,1'b0}		:	next_cnt <=three;		//when cnt=4, if inc=0, next_cnt = three
		{four,1'b1}		:	next_cnt <=zero;		//when cnt=4, if inc=1, next_cnt = zero
		default			:	next_cnt <=3'bx;		//when default, next_cnt = unknown 
		endcase
	end
	
endmodule
