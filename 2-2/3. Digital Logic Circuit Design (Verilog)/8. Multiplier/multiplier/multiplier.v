module multiplier(clk, reset_n, multiplicand, multiplier, op_start, op_clear, result, op_done);	//multiplier
	input 			clk, reset_n, op_start, op_clear;		// clock, Active low reset, Start & Clear operation
	input  [31:0]	multiplier, multiplicand;
	output reg 		op_done;										// Done operation
	output [63:0] 	result;										// Multiplier result

	reg [1:0]  state, nextstate;						// state
	reg [5:0]  exe_count, next_exe_count;			// counting
	reg [31:0] u, v, x;									// u: result from each step, v: overflow bit from u when RSA, x: show each RSC step
	reg [31:0] next_u, next_v, next_x;
	reg 		  x_1, next_x_1;

	wire [31:0] sub, add;								// 32bits subtract, add

	assign add = u + multiplicand;					// define add, sub and result
	assign sub = u + (~multiplicand) + 1'b1;
	assign result = {u,v};
	
	parameter IDLE = 2'b00;								// define IDLE = 00
	parameter EXEC = 2'b01;								// define EXEC = 01
	parameter DONE = 2'b10;								// define DONE = 10

	//sequential circuit
	always@(posedge clk or negedge reset_n) begin		// whenever clk is riging edge or reset_n is falling edge
		if(~reset_n) begin
			state <= IDLE;			// initialization 
			x_1 <= 1'b0; 		// x_1 : 0
			u <= 32'b0;			// u	 : 0
			v <= 32'b0;			// v	 : 0
			x <= 32'b0;			// x	 : 0
			exe_count <= 6'b0; 
			end
		else begin
			state <= nextstate;
			exe_count <= next_exe_count;
			x_1 <= next_x_1;
			u <= next_u;
			v <= next_v;
			x <= next_x;
			end
		end	// the end
	
	always@(op_start, exe_count, op_clear, state, op_done, u, v, x, x_1, add, sub, multiplier) begin // nextstate, output
		if(op_clear)begin					// when op_clear
			next_exe_count <= 6'b0;		// initialization everyting 0
			next_u <= 32'h0;
			next_v <= 32'h0;
			next_x <= 32'b0;
			next_x_1 <= 1'b0;
			nextstate <= IDLE;
			op_done <= 1'b0;
			end
			
		else begin
			case(state)
				IDLE: begin				// IDLE
					if(op_start && !op_clear) begin //if state and not op_clear
						nextstate <= EXEC;
						next_exe_count <= 6'b0;
						next_u <= 32'h0;
						next_v <= 32'h0;
						next_x <= multiplier;
						next_x_1 <= 1'b0;
						op_done <= 1'b0;	 //IDLE => EXEC
						end
						
					else begin
						nextstate <= IDLE;
						next_exe_count <= 6'b0;
						next_u <= 32'b0;
						next_v <= 32'b0;
						next_x <= 32'b0;
						next_x_1 <= 1'b0;
						op_done <= 1'b0;  // stay IDLE
						end
					end	// IDLE end	
						
				EXEC:  begin			//EXEC
					if(op_clear) begin				// when op_clear
						nextstate <= IDLE;			// initialization everyting 0
						next_exe_count <= 7'b0;
						next_u <= 32'b0;
						next_v <= 32'b0;
						next_x <= 32'b0;
						next_x_1 <= 1'b0;
						op_done <= 1'b0;	//EXEC => IDLE
						end
						
					else if(exe_count == 32) begin 
						nextstate <= DONE;
						op_done <= 1'b1;
						next_exe_count <= exe_count;
						next_u <= u;
						next_v <= v;
						next_x <= x;
						next_x_1 <= x_1; //EXEC => DONE
						end
						
					else begin	//EXEC => EXEC
						if({x[0],x_1} == 2'b00) begin	 		// when bit = 00 
							next_x_1<= x[0];   					// shift
							next_u <= {u[31],u[31:1]};
							next_v <= {u[0],v[31:1]};
							next_x <= {x[0],x[31:1]};
							end
				
						else if({x[0],x_1} == 2'b01) begin	// when bit = 01 
							next_x_1 <= x[0];				 		// add and shift
							next_u <= {add[31],add[31:1]};
							next_v <= {add[0],v[31:1]};
							next_x <= {x[0],x[31:1]};
							end
						
						else if({x[0],x_1} == 2'b10) begin	// when bit = 10 
							next_x_1 <= x[0];						// subtract and shift
							next_u <= {sub[31],sub[31:1]};
							next_v <= {sub[0],v[31:1]};
							next_x <= {x[0],x[31:1]};
							end
						
						else if({x[0],x_1} == 2'b11) begin	// when bit = 11
							next_x_1 <= x[0];				  		// shift
							next_u <= {u[31],u[31:1]};
							next_v <= {u[0],v[31:1]};
							next_x <= {x[0],x[31:1]};
							end
						else begin 						
							next_x_1 = 1'b0;
							next_x = 32'b0;
							next_u = 32'b0;
							next_v = 32'b0;
							end
				
						op_done = 1'b0; 					
						next_exe_count = exe_count + 6'b000001;	// increase count
						nextstate <=EXEC; 	//EXEC => EXEC
						end
				end		// EXEC end
							
				DONE: begin		// DONE
					if(op_clear) begin 			//DONE => IDLE
						nextstate <= IDLE;
						next_exe_count <= 6'b0;
						next_u <= 32'b0;
						next_v <= 32'b0;
						next_x <= 32'b0;
						next_x_1 <= 1'b0;
						op_done <= 1'b0;
						end
								
					else if(op_start) begin	//DONE => EXEC
						nextstate <= EXEC;
						next_exe_count <= 6'b0;
						next_u <= 32'h0;
						next_v <= 32'h0;
						next_x <= multiplier;
						next_x_1 <= 1'b0;
						op_done <= 1'b0; 
						end
					
					else begin 
						nextstate <= DONE;		// when stay DONE
						op_done <= 1'b1;
						next_exe_count <= exe_count;
						next_u <= u;
						next_v <= v;
						next_x <= x;
						next_x_1 <= x_1;
						end	
				end	// DONE end
				
				default : begin  //	when default 
					nextstate <= 2'bxx;
					op_done <= 1'bx;
					next_exe_count <= 6'bx;
					next_u <= 32'bx;
					next_v <=32'bx;
					next_x <= 32'bx;
					next_x_1 <= 1'bx;
					end	// default end
			endcase	// case end
		end	// else end
	end	// always end
endmodule
		