`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2024 19:31:06
// Design Name: 
// Module Name: top
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


module top(
    input clk_100MHz,       // 100MHz from Basys 3
    input reset,            // btnC
    input [7:4] JB,         // PMOD JB
    output [1:0] LED,       // LED[1], LED[0]
    output [3:0] an,        // 7 Segment anodes
    output [6:0] seg        // 7 Segment cathodes
    );
	
	// Internal wires 
	wire [4:0] w_enc;
	wire w_A, w_B;
	 
	// Instantiate Modules
	debounce db(.clk(clk_100MHz), .Ain(JB[4]), .Bin(JB[5]), .Aout(w_A), .Bout(w_B));
 	encoder enc (.clk(clk_100MHz), .A(w_A), .B(w_B), .BTN(JB[6]), .EncOut(w_enc), .LED(LED));
 	seg7 seg7c (.clk(clk_100MHz), .sw(JB[7]), .enc(w_enc), .anode(an), .seg_out(seg));

endmodule
