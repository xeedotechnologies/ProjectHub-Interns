`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02.02.2024 16:17:43
// Design Name: 
// Module Name: reedsensor
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


module reedsensor (
  input wire clk,
  input wire reset,
  input wire sensor,
  output reg led
);

// Define states for the state machine
parameter IDLE = 2'b00;
parameter DETECTED = 2'b01;

// Define internal signals
reg [1:0] state;

// Define constants for readability
parameter HIGH = 1'b1;
parameter LOW = 1'b0;

always @(posedge clk or posedge reset) begin
  if (reset) begin
    state <= IDLE;
    led <= LOW;
  end else begin
    case (state)
      IDLE: begin
        if (sensor == HIGH) begin
          state <= DETECTED;
          led <= HIGH;
        end
      end
      DETECTED: begin
        if (sensor == LOW) begin
          state <= IDLE;
          led <= LOW;
        end
      end
    endcase
  end
end

endmodule

