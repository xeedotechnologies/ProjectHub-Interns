`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2024 19:32:00
// Design Name: 
// Module Name: seg7
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


module seg7(

    input clk,
    input sw,
    output [4:0] enc,
    output reg [3:0] anode,
    output reg [6:0] seg_out
    );

	reg [17:0] sclk;
	reg [6:0] seg_reg;

	always @(posedge clk)  begin

		if(sw == 1'b0) // if the switch is off , it turns off the LED Display 
			anode <= 4'b1111;	

		
		else
			// 0 ms refresh digit 0
			if(sclk == 0) begin
				anode <= 4'b1110; //turns on the right most LED
				seg_out <= seg_reg;
				sclk <= sclk + 1;
			end

			// 1ms refresh digit 1
			else if(sclk == 100_000) begin
				// display a 1 on the tenth digit if the number is greater than 9
				if(enc > 9) begin
					seg_out <= 7'b1111001; // 1
					anode <= 4'b1101;
				end
									
				sclk <= sclk + 1;									
			end

			//	2ms
			else if(sclk == 200_000)	
				sclk <= 0;

			// increment
			else	
				sclk <= sclk + 1;						
	 end
	 
	 //  Selects the value to display on the seven segment display
	 always @(enc[4] or enc[3] or enc[2] or enc[1] or enc[0])
	   case (enc[4:0])
                    // seg order     gfedcba
			5'b00000 : seg_reg <= 7'b1000000;		// 0
			5'b00001 : seg_reg <= 7'b1111001;		// 1
			5'b00010 : seg_reg <= 7'b0100100;		// 2
			5'b00011 : seg_reg <= 7'b0110000;		// 3
			5'b00100 : seg_reg <= 7'b0011001;		// 4
			5'b00101 : seg_reg <= 7'b0010010;		// 5
			5'b00110 : seg_reg <= 7'b0000010;		// 6
			5'b00111 : seg_reg <= 7'b1111000;		// 7
			5'b01000 : seg_reg <= 7'b0000000;		// 8
			5'b01001 : seg_reg <= 7'b0010000;		// 9
			5'b01010 : seg_reg <= 7'b1000000;		// 10
			5'b01011 : seg_reg <= 7'b1111001;		// 11
			5'b01100 : seg_reg <= 7'b0100100;		// 12
			5'b01101 : seg_reg <= 7'b0110000;		// 13
			5'b01110 : seg_reg <= 7'b0011001;		// 14
			5'b01111 : seg_reg <= 7'b0010010;		// 15
			5'b10000 : seg_reg <= 7'b0000010;		// 16
			5'b10001 : seg_reg <= 7'b1111000;		// 17
			5'b10010 : seg_reg <= 7'b0000000;		// 18
			5'b10011 : seg_reg <= 7'b0010000;		// 19
			default  : seg_reg <= 7'b0111111;       // - 

	   endcase

endmodule
