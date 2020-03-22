module ALUControl(funct, ALUOp, ALU_control_input);			// ALU_control module
  input [5:0] funct;
  input [1:0] ALUOp;				
  output [3:0]ALU_control_input;	

  reg [3:0]ALU_control_input;

always@(funct or ALUOp) begin
  if(ALUOp == 2'b00) ALU_control_input<= 4'b0010; 			// when (ALUOp==00) => load word, store word
  else if(ALUOp == 2'b01) ALU_control_input<= 4'b0110; 	// when (ALUOp==01) => branch
  else if(ALUOp == 2'b10) begin									// when (ALUOp==10) => R_type
      if(funct == 6'b100000)      ALU_control_input<= 4'b0010;	// => add
      else if(funct == 6'b100010) ALU_control_input<= 4'b0110;	// => sub
      else if(funct == 6'b100100) ALU_control_input<= 4'b0000;	// => and
      else if(funct == 6'b100101) ALU_control_input<= 4'b0001;	// => or
      else if(funct == 6'b101010) ALU_control_input<= 4'b0111;	// => slt
      else if(funct == 6'b100111) ALU_control_input<= 4'b1100; // => nor
      //add this function for HW pipeline CPU 
      else if(funct == 6'b000000) ALU_control_input<= 4'b1000; // => sll 
      else if(funct == 6'b000010) ALU_control_input<= 4'b1001;	// => srl
      else if(funct == 6'b000011) ALU_control_input<= 4'b1010;	// => sra
      else                        ALU_control_input<= 4'bxxxx;  
    end
  else  ALU_control_input<= 4'bxxxx;
end

endmodule
