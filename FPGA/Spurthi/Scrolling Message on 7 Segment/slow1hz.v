`timescale 1ns / 1ps

module slow1hz(input cin , output reg cout );
reg [28:0] pc=0;
always @ (posedge cin)
if (pc!=50_00_0000-1)
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
