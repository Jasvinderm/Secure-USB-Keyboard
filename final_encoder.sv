module encrypt (
  			output logic data_out,
				output logic [0:15] lfsr,
				input logic n_reset,
				input logic clock,
				input logic data_in,
				output logic bit_15
			);
			
	logic feedback;
	
always_ff @(negedge clock, negedge n_reset)
	begin
		if(!n_reset)
			begin
				lfsr <= 16'b1010110011100001;
				//lfsr <= {feedback, lfsr[0:14]};
				
			end
		
		else
			begin
				//lfsr <= 16'b1010110011100001;
				lfsr <= {feedback, lfsr[0:14]};
			end
	end
	
always_comb
	begin		
		//feedback = lfsr[0];
		feedback = lfsr[10] ^ (lfsr[12] ^ (lfsr[13] ^ lfsr[15]));
		//lfsr[0] = feedback;
		data_out = data_in ^ lfsr[15];
		bit_15 = lfsr[15];
	end
	//assign data_out = encrypted;
	
endmodule
			
