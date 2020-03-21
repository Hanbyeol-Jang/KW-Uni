module fifo_cal(state, data_count, head, tail, re, we, next_data_count, next_head, next_tail);	//fifo_cal
	input [2:0] state, head, tail;				// 3bits 3 inputs
	input [3:0] data_count;							// 4bits input
	output reg re,we;									// 2 output, reg 
	output reg [3:0] next_data_count;			// 4bits output,reg
	output reg [2:0] next_head, next_tail;		// 3bits output reg
	
	parameter IDLE 	 = 3'b000;					// define IDLE     = 000
	parameter WRITE 	 = 3'b001;					// define WRITE    = 001
	parameter READ 	 = 3'b010;					// define READ     = 010
	parameter WR_ERROR = 3'b011;					// define WR_ERROR = 011
	parameter RD_ERROR = 3'b100;					// define RD_ERROR = 100

	always@(state, head, tail, data_count, we, re)
		begin
			case(state)													// case
			IDLE :														// when state is IDLE 
				begin
					next_tail <= tail;								// tail, head, data_count not change
					next_head <= head;
					next_data_count <= data_count;
					we <= 1'b0;											// write enable, read enable = 0
					re <= 1'b0;
				end
			WRITE : 														// when state is WRITE
				begin
					next_tail <= tail + 3'b001;					// tail +1, data count +1
					next_head <= head;
					next_data_count <= data_count + 4'b0001;
					we <= 1'b1;											// we =1, re =0
					re <= 1'b0;
				end
				
			READ : 														// when state is READ
				begin
					next_tail <= tail;								// head +1
					next_head <= head + 3'b001;
					next_data_count <= data_count - 4'b0001;	// data count +1
					re <= 1'b1;											// re=1, we=0
					we <= 1'b0;
				end	
			default : 													// when default
				begin
					next_tail <= tail;								// keep every previous value
					next_head <= head;
					next_data_count <= data_count;
					re <= 1'b0;											// re, we=0
					we <= 1'b0;
				end
			endcase
		end
	
			
endmodule		
			