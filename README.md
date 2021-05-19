# MSEE_project - Wen (at SJSU)

**Multi-Layer Perceptron (MLP) Hand-written Pattern Number Recognition System On FPGA**

The proposed project is to deploy hardware accelerator FPGA with its inherent parallelism and on-board memory resource to generate a hand-written pattern number recognition system. Computer vision employed in many accelerated applications currently usually requires a combination of electronic digital hardware and machine learning algorithm. Field programmable gate array (FPGA) has the advantages of lower power consumption and latency compared to other hardware such as CPUs, which makes it a perfect choice for an image processing unit. The simple neural network structure MLP could achieve the state-of-art performance with its generalization ability in the neural network research and usage on Intel (Altera) DE10-lite and preserve the process automation. 

In the early stage, we tried to use both SPI and I2C bus for sending weights file from microSD card to FPGA. The diagram looks like below:
![alt text](https://github.com/victor4700/MSEE_project/blob/main/2021-03-24%2004_55_58-Drawing%20--%20SmartDraw.png)

Altera JTAG-to-Avalon-MM Tutorial is written by D.W.Hawkins and could be found at https://forums.parallax.com/discussion/download/110606/altera_jtag_to_avalon_mm_tutorial.pdf
