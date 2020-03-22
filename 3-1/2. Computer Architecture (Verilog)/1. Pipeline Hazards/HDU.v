`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: k.w uni
// Engineer: kimkisun
// 
// Create Date:    18:51:16 06/01/2017 
// Design Name: 
// Module Name:    HDU 
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
module HDU(IDEX_Rt, IFID_Rs, IFID_Rt, IDEX_MemRead, EX_Bubble, PC_Write, IFID_Write
    );		//haavard detection unit
	 
	 input [4:0] IDEX_Rt, IFID_Rs, IFID_Rt;
	 input  IDEX_MemRead;
	 output reg EX_Bubble, PC_Write, IFID_Write;
	 
	 always@(IDEX_MemRead, IDEX_Rt, IFID_Rs, IFID_Rt)
		begin
			if(IDEX_MemRead && ((IDEX_Rt == IFID_Rs) || (IDEX_Rt == IFID_Rt)))		//load and stall
				begin
					EX_Bubble = 1;		//bubble
					PC_Write = 0;
					IFID_Write = 0;
				end
			else
				begin
					EX_Bubble = 0;
					PC_Write = 1;
					IFID_Write = 1;
				end
		end

endmodule
