`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.01.2024 23:02:57
// Design Name: 
// Module Name: BuzzerPWM
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


module BuzzerPWM (
  input wire clk,       // Clock input
  input wire rst,       // Reset input
  output reg pwm_out    // PWM output for the speaker
);

  reg [23:0] counter;    // Counter for PWM generation

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      counter <= 24'b0;
      pwm_out <= 1'b0;
    end else begin
      if (counter == 24'd500000) begin  // Adjust this value for desired frequency
        counter <= 24'b0;
        pwm_out <= ~pwm_out;  // Toggle PWM output
      end else begin
        counter <= counter + 1;
      end
    end
  end

endmodule

