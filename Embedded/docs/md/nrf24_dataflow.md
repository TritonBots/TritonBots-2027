# NRF24 Radio Dataflow

Note that this code is for the both the Radio Base Station STM32 and Robot STM32.
Note that radio communication MUST be done in 2-way communication to debug the robots and send data to the AI algorithm. This feature will be developed later. This doc is a basic functionality for the radio communication.


1. Robot Commands are inputted into the Base Station through some connectivity peripheral from a laptop, most likely the ethernet port or some serial communication
2. The Robot Commands are received in the Base Station and placed in a buffer
3. The buffer is transmitted to the NRF24 Radio via SPI DMA
4. The robot radio receives the signal
5. The robot places the received bytes into a buffer via SPI DMA
6. The robot verifies the command in the buffer
7. The robot parses the command into motor commands
