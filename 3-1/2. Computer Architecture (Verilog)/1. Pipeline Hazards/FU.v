`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: k.w uni
// Engineer: kimkisun
// 
// Create Date:    18:50:47 06/01/2017 
// Design Name: 	 
// Module Name:    FU 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module FU(IDEX_Rs,IDEX_Rt,EXMEM_Rd,EXMEM_RegWrite,MEMWB_Rd,MEMWB_RegWrite,ForwardA,ForwardB
    );
	 
	 input [4:0] IDEX_Rs,IDEX_Rt,EXMEM_Rd,MEMWB_Rd;
	 input EXMEM_RegWrite,MEMWB_RegWrite;
	 output reg [1:0] ForwardA, ForwardB;
	 
	 always@(EXMEM_RegWrite, EXMEM_Rd, IDEX_Rs, MEMWB_RegWrite, MEMWB_Rd)		//forward a
		begin
//			if(MEMWB_RegWrite && (MEMWB_Rd!=0) && !(EXMEM_RegWrite && (EXMEM_Rd!=0)) && (EXMEM_Rd==IDEX_Rs) && (MEMWB_Rd == IDEX_Rs)) ForwardA = 2'b01;
			if(EXMEM_RegWrite && (EXMEM_Rd!=0) && (EXMEM_Rd == IDEX_Rs)) ForwardA = 2'b10;  //1 step
			else if(MEMWB_RegWrite && (MEMWB_Rd!=0) && (EXMEM_Rd!=IDEX_Rs) && (MEMWB_Rd==IDEX_Rs)) ForwardA = 2'b01; //2 step
			else if(MEMWB_RegWrite && (MEMWB_Rd!=0) && !(EXMEM_RegWrite && (EXMEM_Rd!=0)) && (EXMEM_Rd==IDEX_Rs) && (MEMWB_Rd == IDEX_Rs)) ForwardA = 2'b01;	//double data hazzard
			else ForwardA = 2'b00;
		end
		
	 always@(EXMEM_RegWrite, EXMEM_Rd, IDEX_Rt, MEMWB_RegWrite, MEMWB_Rd)		//forward b
		begin
//			if(MEMWB_RegWrite && (MEMWB_Rd!=0) && !(EXMEM_RegWrite && (EXMEM_Rd!=0)) && (EXMEM_Rd==IDEX_Rt) && (MEMWB_Rd == IDEX_Rt)) ForwardB = 2'b01;
			if(EXMEM_RegWrite && (EXMEM_Rd!=0) && (EXMEM_Rd == IDEX_Rt)) ForwardB = 2'b10;		//1step
			else if(MEMWB_RegWrite && (MEMWB_Rd!=0) && (EXMEM_Rd!=IDEX_Rt) && (MEMWB_Rd==IDEX_Rt)) ForwardB = 2'b01;	  //2 step
			else if(MEMWB_RegWrite && (MEMWB_Rd!=0) && !(EXMEM_RegWrite && (EXMEM_Rd!=0)) && (EXMEM_Rd==IDEX_Rt) && (MEMWB_Rd == IDEX_Rt)) ForwardB = 2'b01;	//double data hazard
			else ForwardB = 2'b00;
		end

endmodule
