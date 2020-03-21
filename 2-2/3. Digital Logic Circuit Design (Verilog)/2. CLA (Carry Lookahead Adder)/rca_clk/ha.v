module ha(a, b, s, co);
input a,b;		//input a,b
output s,co;	//output sum,carry out

	assign s = a^b;
	assign co = a&b;
	
endmodule
