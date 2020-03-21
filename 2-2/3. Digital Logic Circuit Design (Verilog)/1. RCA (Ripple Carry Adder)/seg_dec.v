module seg_dec(iHex, oSEG7);
	input [3:0] iHex;
	output reg [6:0] oSEG7;
	
	always @ (iHex)
	begin
		case(iHex)
		4'h0: oSEG7 = 7'b1000000;	//0
		4'h1: oSEG7 = 7'b1111001;	//1
		4'h2: oSEG7 = 7'b0100100;	//2
		4'h3: oSEG7 = 7'b0110000;	//3
		4'h4: oSEG7 = 7'b0011001;	//4
		4'h5: oSEG7 = 7'b0010010;	//5
		4'h6: oSEG7 = 7'b0000010;	//6
		4'h7: oSEG7 = 7'b1111000;	//7
		4'h8: oSEG7 = 7'b0000000;	//8
		4'h9: oSEG7 = 7'b0011000;	//9
		4'ha: oSEG7 = 7'b0001000;	//A
		4'hb: oSEG7 = 7'b0000011;	//B
		4'hc: oSEG7 = 7'b1000110;	//C
		4'hd: oSEG7 = 7'b0100001;	//D
		4'he: oSEG7 = 7'b0000110;	//E
		4'hf: oSEG7 = 7'b0001110;	//F
		default: oSEG7 = 7'b1111111;
		endcase
	end
endmodule
