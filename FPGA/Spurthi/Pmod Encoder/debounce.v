`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2024 19:29:46
// Design Name: 
// Module Name: debounce
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


module debounce(
    input clk,
    input Ain,
    input Bin,
    output Aout,
    output Bout
    );
	 reg r_Aout = 0;
	 reg r_Bout = 0;

	 reg [6:0] sclk = 0;
	 reg sampledA = 0;
	 reg sampledB = 0;
	 
	 always @(posedge clk) begin
			sampledA <= Ain;
			sampledB <= Bin;
			// clock is divided to 1MHz
			// samples every 1uS to check if the input is the same as the sample
			// if the signal is stable, the debouncer should output the signal
			
			if(sclk == 100) begin
					if(sampledA == Ain) begin
							r_Aout <= Ain;
					end
					
					if(sampledB == Bin) begin
							r_Bout <= Bin;
					end
					
					sclk <= 0;
			end
			else begin
					sclk <= sclk + 1;
			end
	 end

    assign Aout = r_Aout;
    assign Bout = r_Bout;

endmodule


