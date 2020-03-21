module mx2_to_ff(d0,d1,s,y);			//32bits mx
input      [31:0]   d0,d1;				//32bits input d0,d1
input               s;					//input 
output   [31:0]   y;						//32bits output


assign y=(s==1'b0) ? d0 : d1;					// if s= 0, y=d0, else y=d1

endmodule
