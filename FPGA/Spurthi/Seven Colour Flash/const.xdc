# Clock signal
set_property PACKAGE_PIN W5 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]

# Reset signal
set_property PACKAGE_PIN W8 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]

set_property PACKAGE_PIN A14 [get_ports {led}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {led}]

set_property SEVERITY {Warning} [get_drc_checks UCIO-1]