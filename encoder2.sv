//LFSR = Module Name
//Reset = Reset on flip flop
//clk = Clock
//q = q output after each flipflop
//feedback_line = Wire fed back from the final flop flop
//data_in = data coming in from the keyboard
//data_out = encrypted data going out of the IlBagato

module LFSR (reset, clk, data_in, data_out);
  //Defining all inputs
	input clk, reset, data_in;
	//Defining all outputs
	//output [15:0] q, 
	output data_out;
	
	reg[15:0] LFSR;
	//wire feedback_line;

	always @(posedge clk)
	
		begin
		
			if(!reset)
				
				begin
					LFSR[15:0] <= 15'h9C;
				end
			else
				
				begin
				
							LFSR[0] <= (LFSR[10]^(LFSR[12]^(LFSR[13]^LFSR[15])));
							LFSR[14:0] <= LFSR[15:1];
		
				end		
	   
		
	end	
 //assign q = LFSR;	
	
endmodule
