module lfsr #(parameter N = 16)
             (output logic [N-1:0]q, [N-1:0]out,
  		  input logic clock, n_reset);
			  

			  
			  
	logic feedback;
	
	int i;
	int j;
	int k;
	logic in <= 16'b0000000000011100;
	logic [N-1:0] taps;
	logic [N-1:0] store;
	//wire [N-1:0] in; //date coming from the keyboard

	
initial
begin
	taps = '0;
	taps |= ((1'b1 << 0) | (1'b1 << 2) | (1'b1 << 3) | (1'b1 << 5)); //setting appropriate tap bits to 1 for comb block
end

always_ff @(posedge clock, negedge n_reset) //we think n_reset needs to be triggered everytime the encrypted key is sent
	begin
	if (~n_reset)
		begin
			q <= 16'b1010110011100001; //this resets the initial q register to default value ready for next encryption
			store <='0; //resets all of the store register's bits to 0 ready for next input from keyboard 
		end
	else
		begin
		q <= {feedback, q[N-1:1]}; //this shifts the bits and brings back the feedback into the 'zeroth' bit
		for (i=15; i>=0; i--)
			store[i] = in[i];	//this stores the input hex value from keyboard bit by bit into the store register
		end
	end
	

always_comb
	begin
	feedback = q[0]; //sets the 'zeroth' bit as what feedback is from the combinational logic
	for (j=1; j<=N-1; j++)																															   
		if (taps[i])		  //if taps is '1' it goes into the combinational logic to encrypt. We set bits 16, 14, 13, 11 of taps to '1' at the start
			feedback ^= q[i]; //performs the LFSR combinational logic
	end

always_comb
begin
	for (k=15; k>=0; k--) //for loop to ensure all the encrypted bits have been sent to the combinational logic
		begin
		out[k] <= (store[k]^q[k]); //this XORs each keyboard bit with the corresponding LFSR bit, and assigns that to the correct 'out' register's bit.
		end
		
end
	
		//n_reset <= 1'b1; //we don't know

		
endmodule


	
