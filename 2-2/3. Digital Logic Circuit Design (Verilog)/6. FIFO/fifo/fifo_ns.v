module fifo_ns(rd_en, wr_en, state, data_count, next_state);   //fifo_ns logic
	input rd_en, wr_en;						// 2 inputs
	input [2:0] state;						// 3bits input
	input [3:0] data_count;					// 4bits input
	output[2:0] next_state;					// 3bits output
	reg[2:0] next_state;						// 3bits reg
	
	parameter IDLE 	 = 3'b000;			// define IDLE     = 000
	parameter WRITE 	 = 3'b001;			// define WRITE    = 001
	parameter READ 	 = 3'b010;			// define READ     = 010
	parameter WR_ERROR = 3'b011;			// define WR_ERROR = 011
	parameter RD_ERROR = 3'b100;			// define RD_ERROR = 100
	
	
	always@(state or wr_en or rd_en or data_count)
	begin
		case(state)																// case
			IDLE : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when state is IDLE 
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else if (wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			READ : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when state is READ
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else if(wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			RD_ERROR : if(wr_en==0 && rd_en==0) next_state <= IDLE; // when state is RD_ERROR
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==0 && rd_en==1 && data_count == 4'b0000) next_state <= RD_ERROR;
					 else	next_state <= 3'bxxx;
					 
			WR_ERROR : if(wr_en==0 && rd_en==0) next_state <= IDLE;	// when state is WR_ERROR
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else	next_state <= 3'bxxx;
					 
			WRITE : if(wr_en==0 && rd_en==0) next_state <= IDLE;		// when state is WRITE
					 else if(wr_en==1 && rd_en==0 && data_count<4'b1000) next_state <= WRITE;
					 else if(wr_en==1 && rd_en==0 && data_count == 4'b1000) next_state <= WR_ERROR;
					 else if(wr_en==0 && rd_en==1 && data_count > 4'b0000) next_state <= READ;
					 else	next_state <= 3'bxxx;
					 
			default : next_state <= 3'bx;										//when default, unknown
		endcase
	end
	
endmodule
