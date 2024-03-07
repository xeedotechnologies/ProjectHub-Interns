`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.01.2024 13:52:01
// Design Name: 
// Module Name: SevenColorFlash
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


module LEDBlink (
  input wire clk,   // Clock input
  input wire rst,   // Reset input
  output reg led    // LED output
);

  reg [23:0] counter;   // Counter for timing

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      counter <= 24'b0;
      led <= 1'b0;  // Initial state is OFF
    end else begin
      if (counter == 500) begin  // Adjust this value for the desired delay
        counter <= 24'b0;
        led <= ~led;  // Toggle the LED state
      end else begin
        counter <= counter + 1;
      end
    end
  end

endmodule


