module test_lfsr;
logic n_reset, clock;
logic [15:0]q;

lfsr d0 (.*);

initial
  begin
	clock = '0;
	forever
		#5ns clock = ~clock;
	end

initial
	begin
	n_reset = '1;
	#10ns n_reset = '0;
	#10ns n_reset = '1;
	#100ns n_reset = '0;
	#110ns n_reset = '1;
	end
	
endmodule
