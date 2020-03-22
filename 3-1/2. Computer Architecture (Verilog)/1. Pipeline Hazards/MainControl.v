//MainControl module
module MainControl(op,RegDst,Jump,Branch,MemRead,MemtoReg,ALUOp,MemWrite,ALUSrc,RegWrite,Jal);
input [5:0]op;                                                        //input 6bit op code
output RegDst,Jump,Branch,MemRead,MemtoReg,MemWrite,ALUSrc,RegWrite,Jal;  //output 1bit signals
output [1:0]ALUOp;                                                    //output 2bit ALU Control op code  

reg RegDst,Jump,Branch,MemRead,MemtoReg,MemWrite,ALUSrc,RegWrite,Jal;
reg [1:0]ALUOp;

//combinatinal logic. we us always sentence
always@(op)begin
  if(op==6'b00000)begin   // R_TYPE
    ALUSrc		<=1'b0;    // o
    RegDst		<=1'b1;    // 1
    RegWrite	<=1'b1;    // 1
    MemtoReg	<=1'b0;    // o
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b0;    // o
    ALUOp		<=2'b10;   // 1o
    Jump			<=1'b0;    // o
    Branch		<=1'b0;    // o
    Jal 			<= 1'b0;
    end
else if(op==6'b100011) begin // lw
    ALUSrc		<=1'b1;     // 1
    RegDst		<=1'b0;     // o
    RegWrite	<=1'b1;  	// 1
    MemtoReg	<=1'b1;  	// 1
    MemRead		<=1'b1;   	// 1
    MemWrite	<=1'b0;  	// o
    ALUOp		<=2'b00;    // oo
    Jump			<=1'b0;     // o
    Branch		<=1'b0;     // o
    Jal 			<= 1'b0;
    end
else if(op==6'b101011) begin // sw
    ALUSrc		<=1'b1;     // 1
    RegDst		<=RegDst;     // don't care
    RegWrite	<=1'b0;   // o
    MemtoReg	<=MemtoReg;   // don't care
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b1;   // 1
    ALUOp		<=2'b00;     // o
    Jump			<=1'b0;       // o
    Branch		<=1'b0;       // o
    Jal 			<= 1'b0;
    end
  else if(op==6'b000100) begin // beq
    ALUSrc		<=1'b0;     // o
    RegDst		<=RegDst;     // don't care
    RegWrite	<=1'b0;   // o
    MemtoReg	<=MemtoReg;   // don't care
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b0;   // o
    ALUOp		<=2'b01;     // 1
    Jump			<=1'b0;       // o
    Branch		<=1'b1;       // 1
    Jal 			<= 1'b0;
    end
  else if(op==6'b000010) begin // jump
    ALUSrc		<=ALUSrc;     // don't care
    RegDst		<=RegDst;     // don't care
    RegWrite	<=1'b0;   // o
    MemtoReg	<=MemtoReg;   // don't care
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b0;   // o
    ALUOp		<=ALUOp;     // don't care
    Jump			<=1'b1;       // 1
    Branch		<=1'b0;     // o
    Jal 			<= 1'b0;
    end
  else if(op==6'b001000) begin // addi
    ALUSrc		<=1'b1;     // 1
    RegDst		<=1'b0;     // o
    RegWrite	<=1'b1;   // 1
    MemtoReg	<=1'b0;   // 0
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b0;   // o
    ALUOp		<=2'b00;     // 00
    Jump			<=1'b0;       // 0
    Branch		<=1'b0;     // o
    Jal 			<= 1'b0;
    end
  else if(op==6'b000011) begin // jal
    ALUSrc		<=1'b0;     // 0
    RegDst		<=1'b0;     // o
    RegWrite	<=1'b1;   // 1
    MemtoReg	<=1'b0;   // 0
    MemRead		<=1'b0;    // o
    MemWrite	<=1'b0;   // o
    ALUOp		<=2'b00;     // 00
    Jump			<=1'b1;       // 1
    Branch		<=1'b0;     // o
    Jal 			<= 1'b1;		 // 1		
    end
  else begin
    ALUSrc		<=ALUSrc;     // don't care
    RegDst		<=RegDst;     // don't care
    RegWrite	<=RegWrite;   // don't care
    MemtoReg	<=MemtoReg;   // don't care
    MemRead		<=MemRead;    // don't care
    MemWrite	<=MemWrite;   // don't care
    ALUOp		<=ALUOp;     // don't care
    Jump			<=Jump;       // don't care
    Branch		<=Branch;     // don't care
    Jal			<=Jal;
    end
end
endmodule
