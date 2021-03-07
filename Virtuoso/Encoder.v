//Verilog HDL for "ADC_2bit", "encoder" "functional"


module encoder (in1, in2, in3, in4 , out1, out2);

input  in1, in2, in3, in4; 
output out1, out2;
reg out1_r, out2_r;

wire [3:0] in;
assign in[0] = in1;
assign in[1] = in2;
assign in[2] = in3;
assign in[3] = in4;

assign out1 = out1_r;
assign out2 = out2_r;

always@(*)
begin
	case(in)
	4'b0000 : begin
		out1_r <= 1'b0;
		out2_r <= 1'b0;
	end

	4'b0010 : begin 
		out1_r <= 1'b1;
		out2_r <= 1'b0;
		end
	4'b0110 : begin
		out1_r <= 1'b0;
		out2_r <= 1'b1;
	end
	4'b1110 : begin
		out1_r <= 1'b1;
		out2_r <= 1'b1;
	end
	default : begin
		out1_r <= 1'bz;
		out2_r <= 1'bz;
	end
	endcase
end
endmodule
