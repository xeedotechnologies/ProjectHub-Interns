`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02.02.2024 14:54:49
// Design Name: 
// Module Name: motion
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


module motion (
  input wire clk,          // Clock signal
  input wire pirSensor,    // PIR sensor input
  output reg led           // LED output
);

  // States definition
  localparam IDLE = 2'b00;
  localparam MOTION_DETECTED = 2'b01;
  localparam MOTION_ENDED = 2'b10;

  // Registers
  reg [1:0] currentState, nextState;

  // Always block for state transitions
  always @(posedge clk) begin
    currentState <= nextState;
  end

  // Combinational always block for state and output logic
  always @* begin
    case (currentState)
      IDLE:
        begin
          led = 0; // LED OFF
          if (pirSensor) begin
            nextState = MOTION_DETECTED;
          end else begin
            nextState = IDLE;
          end
        end
      MOTION_DETECTED:
        begin
          led = 1; // LED ON
          if (!pirSensor) begin
            nextState = MOTION_ENDED;
          end else begin
            nextState = MOTION_DETECTED;
          end
        end
      MOTION_ENDED:
        begin
          led = 0; // LED OFF
          if (pirSensor) begin
            nextState = MOTION_DETECTED;
          end else begin
            nextState = IDLE;
          end
        end
      default:
        nextState = IDLE;
    endcase
  end

endmodule



