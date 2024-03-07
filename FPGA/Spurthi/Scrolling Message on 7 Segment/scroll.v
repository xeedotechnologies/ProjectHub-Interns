`timescale 1ns / 1ps


module scroll( input clk , input rst , output [6:0]seg , output reg [3:0] an);
wire sc1hz;
wire sc100hz;
reg[2:0]s;
reg[3:0]a,b,c,d;
reg [3:0] o; 
slow1hz(clk , sc1hz);
slow100hz(clk ,sc100hz);

always @(posedge sc1hz or posedge rst)
begin
if(rst)
s<=0; 
else if (s==4) 
s<=1;
else
s<=s+1; 
end 

always @ (posedge sc1hz)
begin
case(s) 
0:
begin 
a=0;
b=1;
c=2;
d=3; 
end 
 
1:
begin 
a=1;
b=2;
c=3;
d=0; 
end 

2:
begin 
a=2;
b=3;
c=0;
d=1; 
end

3:
begin 
a=3;
b=0;
c=1;
d=2; 
end


4:
begin 
a=0;
b=1;
c=2;
d=3; 
end 
endcase
end 

reg [1:0] count;
always @(posedge sc100hz or posedge rst)
begin
if(rst)
count <=0;
else
begin
 count<=count+1;

case (count)
2'b00:
begin
o=d; 
an=4'b1110;
end 

2'b01:
begin
o=c; 
an=4'b1101;
end 

2'b10:
begin
o=b; 
an=4'b1011;
end 

2'b11:
begin
o=a; 
an=4'b0111;
end
endcase 
end 
end



seg7 dut ( o , seg);
 
endmodule
