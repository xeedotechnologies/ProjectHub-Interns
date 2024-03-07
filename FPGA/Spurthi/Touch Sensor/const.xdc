# Assuming you are using Basys3 board
#set_property -dict {PACKAGE_PIN J15 IOSTANDARD LVCMOS33} [get_ports {touch_signal}]
#set_property -dict {PACKAGE_PIN H17 IOSTANDARD LVCMOS33} [get_ports {touched}]
set_property PACKAGE_PIN A14 	 [get_ports {touch_signal}]					
set_property IOSTANDARD LVCMOS33 [get_ports {touch_signal}]

set_property PACKAGE_PIN U16 [get_ports {touched}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {touched}]	

set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]	


set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets touch_signal_IBUF] 

	
###Sch name = JA1
#set_property PACKAGE_PIN J1 [get_ports {touched}]					
#	set_property IOSTANDARD LVCMOS33 [get_ports {touched}]	