`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02.02.2024 14:28:28
// Design Name: 
// Module Name: buttonswitch
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


module buttonswitch(
    input btn,      // Button input
    output reg LED // LED output
);


// Define the LED and button signals
reg btn_reg;


// Assign button signal
always @ (posedge btn)
    btn_reg <= ~btn_reg;


// Toggle LED when button is pressed
always @ (posedge btn_reg)
    LED <= ~LED;


endmodule
