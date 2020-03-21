module fa(a,b,ci,s,co); 

input a,b,ci;         //input a,b,carry in
output s,co;          //output sum,carry out
wire c1,c2,sm;        //use 3 wire

ha U0_ha(.a(a),.b(b),.s(sm),.co(c1));		//express full adder
ha U1_ha(.a(sm),.b(ci),.s(s),.co(c2));		//by instance
_or2 U2_or2(.a(c1),.b(c2),.y(co));

endmodule
