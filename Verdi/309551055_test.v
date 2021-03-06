module test;

reg[7:0] in;
reg clk,reset;
wire[7:0] out;

initial begin
	clk=0;
	forever
    #5 clk = !clk;
end

initial begin
    $dumpfile("cpu.vcd");
    $dumpvars;	
end

cpu cc(.in(in), .clk(clk), .reset(reset), .out(out));

initial begin
	in    =8'b00000000;
	reset =1'b1;

//write your test pattern----------------

#12 in = 8'b11110000;//default
	reset =1'b0;

#10 in = 8'b10000011;//store data in addr:0011
#10 in = 8'b11111111;//store -1 in addr:0011

#10 in = 8'b10001100;//store data in addr:1100//!!!!!
#10 in = 8'b00000000;//store 0 in addr:1100

#10 in = 8'b10000000;//store data in addr:0000
#10 in = 8'b11111111;//store -1 in addr:1100

#10 in = 8'b10100011;//C = mem[addr:0011](48)
#10
#10 in = 8'b10101100;//C = mem[addr:1100](-1)
#10
#10 in = 8'b10100000;//C = mem[addr:1100](0)
#10
#10 in = 8'b01100000;//input A
#10 in = 8'b00000000;//A=0
#10 in = 8'b01110000;// input B
#10 in = 8'b11111111;//B=0
#10 in = 8'b00010000;//C = A(0)-B(0)
#10 in = 8'b00100000;//C = A(0) + 1 C=1
#10 in = 8'b00110000;//C=A(0)-1 , C=-1 
#10 in = 8'b10011000;//store C(-1) in addr:1000
#10 in = 8'b11010000;//A=C(-1)
#10 in = 8'b11100000;//B=C(-1)
#10 in = 8'b00000000;//C = A(-1)+B(-1)
#10 in = 8'b01000000;//C = A(-1)+ B(-1) + 1
#10 in = 8'b10110000;//output C(-2)
#10 in = 8'b01010000;//C=-A
#10 in = 8'b11000011;//output mem[addr:0011](48)
#10
#10 in    =8'b00000000;
	reset =1'b1;
//----------------------------------------
#10  $finish;

end
endmodule