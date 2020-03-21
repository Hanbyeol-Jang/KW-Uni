module fifo_out(state, data_count, empty, full, rd_ack, rd_err, wr_ack, wr_err);	//fifo_out
	input [2:0] state;															// 3 bits input
	input [3:0] data_count;														// 4 bits intput
	output reg empty, full, rd_ack, rd_err, wr_ack, wr_err;			// output,reg

	
	parameter IDLE 	 = 3'b000;					// define IDLE     = 000
	parameter WRITE 	 = 3'b001;					// define WRITE    = 001
	parameter READ 	 = 3'b010;					// define READ     = 010
	parameter WR_ERROR = 3'b011;					// define WR_ERROR = 011
	parameter RD_ERROR = 3'b100;					// define RD_ERROR = 100
	
	always @ (data_count)		
	begin
		if(data_count==0)										// no data, empty
			begin
				full<=0; empty<=1;
			end
		else if(data_count==4'b1000)						// when data is 8, full
			begin
				full<=1; empty<=0;
			end
		else
			begin													// otherwise full =0, empty=0
				full<=0; empty<=0;
			end
	end
	
	always @ (state)		
	begin
		case(state)
			
			IDLE : 																	// when IDLE, every value : 0
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=0; rd_err<=0;
				end
				
			WRITE : 																	// when WRITE, only wr_ack =1, the others =0
				begin
					wr_ack<=1; wr_err<=0; rd_ack<=0; rd_err<=0;
				end
			
			READ : 																	// when READ, only rd_ack =1, the others =0
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=1; rd_err<=0;
				end
				
			WR_ERROR : 																// when WR_ERROR, only wr_err =1, the others =0
				begin
					wr_ack<=0; wr_err<=1; rd_ack<=0; rd_err<=0;
				end
				
			RD_ERROR : 																// when RD_ERROR, only rd_err =1, the others =0
				begin
					wr_ack<=0; wr_err<=0; rd_ack<=0; rd_err<=1;
				end
				
			default : 																// when default, unknown
				begin
					wr_ack<=1'bx; wr_err<=1'bx; rd_ack<=1'bx; rd_err<=1'bx;
				end
		endcase
	end
	
endmodule
