`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.01.2024 10:16:46
// Design Name: 
// Module Name: TouchSensor
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


module TouchSensor (
  input wire touch_signal,
  output reg touched
);

  reg touch_state, touch_state_next;

  // Sequential logic to detect touch
  always @(posedge touch_signal) begin
    touch_state <= touch_state_next;
  end

  // Combinational logic to update touch state
  always @(touch_state) begin
    // You may need to adjust the condition based on the touch sensor behavior
    touch_state_next = (touch_state == 0 && touch_signal == 1'b1) ? 1'b1 : 1'b0;
  end

  // Output assignment
  always @(posedge touch_signal) begin
    touched <= touch_state;
  end

endmodule

