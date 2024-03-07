# Set I/O standard and pin location for external button input (assuming it's connected to pin P12)
set_property -dict {PACKAGE_PIN A15 IOSTANDARD LVCMOS33} [get_ports {btn}]


# Set I/O standard and pin location for LED output (assuming it's connected to pin N13)
set_property -dict {PACKAGE_PIN U16 IOSTANDARD LVCMOS33} [get_ports {LED}]


set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_IBUF]


set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]