//Data Memory module
module DM(i_clk, MemRead, MemWrite,i_addr, i_data, o_data);

  input i_clk, MemRead, MemWrite;   //input 1bit clock, read and write signal
  input [31:0]i_addr;               //input 32bit address
  input [31:0]i_data;               //input 32bit data
  output [31:0]o_data;              //output 32bit data
  
  reg [31:0] o_data;
  
  reg [7:0]mem[255:0];             //8bit data memory array

  initial
  begin
    $readmemb("data_memory.txt",mem); //readmemb read binary number from data_memory.txt and store to data memory
  end

  //data memory is edge-triggered for writes
  //Data memeory is reverse order 
  always@(posedge i_clk) begin
    if(MemRead==1'b0 && MemWrite==1'b1) begin
            mem[i_addr+3]<=i_data[7:0];
            mem[i_addr+2]<=i_data[15:8];
            mem[i_addr+1]<=i_data[23:16];
            mem[i_addr]<=i_data[31:24];
    end
    else begin
				mem[i_addr+3]	<=	mem[i_addr+3];
				mem[i_addr+2]	<= mem[i_addr+2];
				mem[i_addr+1]	<=	mem[i_addr+1];
				mem[i_addr]		<= mem[i_addr];
	 end
  end
    
  //read  
  always@(MemRead or MemWrite or i_addr) begin
        if(MemRead==1'b1 && MemWrite==1'b0)
          begin
            o_data[7:0] <=mem[i_addr+3];
            o_data[15:8] <=mem[i_addr+2];
            o_data[23:16] <=mem[i_addr+1];
            o_data[31:24] <=mem[i_addr];
          end
        else if(MemRead==1'b0 && MemWrite==1'b0)  //for first machine code : 000000000 000000000 000000000 000000000
            o_data <= 32'h00000000;               //if not this condition, o_data output dont'care value. We don't want to see don't care value 
      else;                                         
 end

endmodule

