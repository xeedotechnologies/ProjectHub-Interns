`timescale 1ns / 1ps


module seg7( input [3:0] y , output reg [6:0] disp );
always @(y)
begin
case(y)
0: disp= 7'b0011000;
1: disp= 7'b0110000;
2: disp= 7'b0100100;
3: disp= 7'b1000001;
endcase
end
endmodule
