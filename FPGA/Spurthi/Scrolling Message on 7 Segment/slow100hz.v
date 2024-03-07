`timescale 1ns / 1ps

module slow100hz( input cin , output reg cout);
reg [28:0] pc=0;
always @ (posedge cin)
if (pc!=5000-1)
begin
pc<=pc+1;
cout=0;
end
else
begin
pc<=0;
cout<=1;
end
endmodule


