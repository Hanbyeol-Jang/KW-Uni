module bus_arbit(m0_req, m1_req, clk, reset_n, m0_grant, m1_grant);		//bus arbiter
	input m0_req, m1_req, clk, reset_n;		// 4 inputs
	output m0_grant, m1_grant;					// 2 outputs
	
	reg [1:0] state;								// 2bits reg(current state)
	reg [1:0] next_state;						// 2bits reg(next state)
	
	parameter M0_Grant = 2'b10;				// define M0_Grant=10
	parameter M1_Grant = 2'b01;				// define M1_Grant=01
	
	always @(posedge clk or negedge reset_n)			// whenever clk is rising edge or reset_n is falling edge
	begin
		if(reset_n==1'b0)	state <= M0_Grant;			// if reset = 0, state is M0_Grant
		else					state <= next_state;			// otherwise, next state			
	end
	
	always @(m0_req, m1_req, state, next_state)	
	begin
		case(state)				
			M0_Grant	:																// when state is M0_Grant
			begin	
				if(m0_req==1'b0&&m1_req==1'b1)								next_state	<=	M1_Grant;	// if m0_req = 0 and m1_req = 1, move to M1_Grant
				else if((m0_req==1'b0&&m1_req==1'b0)||m0_req==1'b1)	next_state	<=	M0_Grant;	// otherwise, keep position	
				else 																	next_state <= 2'bx;			// else, unknown
			end
			
			M1_Grant	:																// when state is M1_Grant
			begin	
				if(m1_req==1'b0)			next_state	<=	M0_Grant;	// if m1_req = 0, move to M0_Grant
				else if(m1_req==1'b1)	next_state	<=	M1_Grant;	// otherwise, keep position
				else							next_state <=2'bx;			// else, unknown
			end
			
			default	:	next_state	<=	2'bx;		//when default, unknown
		endcase
	end
	
	assign {m0_grant, m1_grant} = state;		// m1_grant, m0_grant = state
	
endmodule
