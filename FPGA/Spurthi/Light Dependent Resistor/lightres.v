`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.02.2024 19:53:17
// Design Name: 
// Module Name: lightres
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


module lightres (
  input wire clk,
  input wire reset,
  output reg led
);

// Define constants for readability
parameter HIGH = 1'b1;
parameter LOW = 1'b0;

reg [31:0] counter;
reg [9:0] sensorValue;

always @(posedge clk or posedge reset) begin
  if (reset) begin
    led <= LOW; // Initial state: LED is off
    counter <= 0;
    sensorValue <= 0;
  end else begin
    // Toggle LED every 1-second delay
    if (counter == 50000000) begin // Assuming a 50 MHz clock
      led <= ~led;
      counter <= 0;
    end else begin
      counter <= counter + 1;
    end

    // Simulate analogRead behavior with a counter
    if (counter % 100000 == 0) begin
      sensorValue <= sensorValue + 1;
    end
  end
end

endmodule

