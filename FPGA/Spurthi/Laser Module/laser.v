`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.02.2024 16:32:59
// Design Name: 
// Module Name: laser
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


module laser (
  input wire clk,
  input wire reset,
  output reg laserHead
);

// Define constants for readability
parameter HIGH = 1'b1;
parameter LOW = 1'b0;

reg [31:0] counter;

always @(posedge clk or posedge reset) begin
  if (reset) begin
    laserHead <= LOW; // Initial state: Laser head is off
    counter <= 0;
  end else begin
    // Toggle laserHead every 1-second delay
    if (counter == 50000000) begin // Assuming a 50 MHz clock
      laserHead <= ~laserHead;
      counter <= 0;
    end else begin
      counter <= counter + 1;
    end
  end
end

endmodule
