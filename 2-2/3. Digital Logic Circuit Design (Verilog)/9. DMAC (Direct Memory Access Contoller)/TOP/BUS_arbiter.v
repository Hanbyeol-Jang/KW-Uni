module BUS_arbiter(clk, reset_n, M0_req, M1_req, M0_grant, M1_grant);		//bus arbiter
	input clk, reset_n, M0_req, M1_req;		// 4 inputs
	output reg M0_grant, M1_grant;					// 2 outputs
	
	reg state, next_state;						// reg

	parameter M0_Grant = 1'b0;				// define M0_Grant=10
	parameter M1_Grant = 1'b1;				// define M1_Grant=01
	
	always @(posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n==1'b0)	state <= M0_Grant;			// if reset = 0, state is M0_Grant
		else					state <= next_state;			// otherwise, next state			
	end
	
	always @(M0_req, M1_req, state)
	begin
		case(state)				
			M0_Grant	:																// when state is M0_Grant
				begin	
					if(M0_req==1'b0&&M1_req==1'b1)								next_state = M1_Grant;	// if m0_req = 0 and m1_req = 1, move to M1_Grant
					else if((M0_req==1'b0&&M1_req==1'b0)||M0_req==1'b1)	next_state = M0_Grant;	// otherwise, keep position	
					else 																	next_state = state;		// else,
				end
				
			M1_Grant	:																// when state is M1_Grant
				begin	
					if(M1_req==1'b1)			next_state = M1_Grant;	// if m1_req = 0, move to M0_Grant
					else if(M1_req==1'b0&&M0_req==1'b1)	next_state <= M0_Grant;	// otherwise, keep position
					else							next_state = state;			// else, unknown
				end
			default	:	next_state <= 1'bx;		//when default, unknown
		endcase
	end
	
	always@(M0_req, M1_req, state)
	begin
		case(state)
			M0_Grant : 						// when state is M0_Grant
				begin
					M0_grant = 1;
					M1_grant = 0;
				end
			M1_Grant : 						// when state is M1_Grant
				begin
					M0_grant = 0;
					M1_grant = 1;
				end
			default : 					 	// when default
				begin
					M0_grant = 0;
					M1_grant = 0;
				end
		endcase
	end
endmodule
