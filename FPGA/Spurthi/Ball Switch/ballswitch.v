`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.02.2024 14:07:25
// Design Name: 
// Module Name: ballswitch
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ballswitch( input wire clk , 
input wire rst , 
input wire sensor , 
output reg led );

localparam low = 1'b0;
localparam high = 1'b1;

always @ (posedge clk or posedge rst)
begin
    if(rst)
    begin
    led<=low;
    end 
else begin
    if(sensor == high)begin
    led<= high; 
    end
    else begin
    led<=low;
    end 
    end
end 
endmodule
