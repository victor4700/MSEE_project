//this is a top module 

module top(
	input MAX10_CLK1_50,
	input SCL,
	inout SDA,
	input FINISH,
	//input FIN,
	output[9:0] LEDR,
	output[7:0] SEG0,
	output[7:0] SEG1,
	output[7:0] SEG2,
	output[7:0] SEG3,
	output[7:0] SEG4,
	output[7:0] SEG5,
	
	input 		     [1:0]		KEY,
	
		//////////// SDRAM //////////
	output		    [12:0]		DRAM_ADDR,
	output		     [1:0]		DRAM_BA,
	output		          		DRAM_CAS_N,
	output		          		DRAM_CKE,
	output		          		DRAM_CLK,
	output		          		DRAM_CS_N,
	inout 		    [15:0]		DRAM_DQ,
	output		          		DRAM_LDQM,
	output		          		DRAM_RAS_N,
	output		          		DRAM_UDQM,
	output		          		DRAM_WE_N
	
	
);
	
	wire write_finished_signal;
	wire read_finished_signal;
	wire [31:0] READ_DATA;
	
	
	wire [7:0] DOUT_L, DOUT_L2, DOUT_L3, DOUT_H;
	wire [7:0] hex1, hex2, hex3;
	
	assign hex3 = READ_DATA[31:24];
	assign hex2 = READ_DATA[23:16];
	assign hex1 = READ_DATA[15:8];
	assign LEDR[7:0] = READ_DATA[7:0];
	
	
	assign LEDR[9] = write_finished_signal;
	assign LEDR[8] = read_finished_signal;
	
	display_output d(hex1, hex2, hex3, SEG0, SEG1, SEG2, SEG3, SEG4, SEG5);
	sdram_loader s(
	.MAX10_CLK1_50(MAX10_CLK1_50),
	.SCL(SCL),
	.SDA(SDA),
	.FINISH(FINISH),		//from Arduino, not used yet
	.READ_DATA(READ_DATA),		//from read command, to top -> display
	.write_finished_signal(write_finished_signal),
	.read_finished_signal(read_finished_signal),
	
	.KEY(KEY),
	
	//////////// I2C_slave //////////
	//.FIN(FIN),
	
	//////////// SDRAM //////////
	.DRAM_ADDR(DRAM_ADDR),
    .DRAM_BA(DRAM_BA),
    .DRAM_CAS_N(DRAM_CAS_N),
    .DRAM_CKE(DRAM_CKE),
    .DRAM_CLK(DRAM_CLK),
    .DRAM_CS_N(DRAM_CS_N),
    .DRAM_DQ(DRAM_DQ),
    .DRAM_LDQM(DRAM_LDQM),
    .DRAM_RAS_N(DRAM_RAS_N),
    .DRAM_UDQM(DRAM_UDQM),
    .DRAM_WE_N(DRAM_WE_N)
	);
	
	

	
	//assign LEDR[7:0] = write_data[7:0];
	//assign hex1 = write_data[15:8];
	//assign hex2 = write_data[23:16];
	//assign hex3 = write_data[31:24];
	
	
endmodule
