/**
   @file NRF24L01P_packet.h
   
   @brief contains packet format and length information for the NRF24L01+

   This makes it easier to find the same information from the datasheet.
   This may not be used in the STM32 code, but it might be useful to know.

   @see Embedded\docs\nRF24L01P_Product_Specification_1_0.pdf
   
   Information is from the datasheet pages: 28-29, 49.
*/

/*
Enhanced ShockBurst™ Packet Format
| Preamble |  Address  | Packet Control Field |  Payload   |   CRC     |
|  1 byte  | 3-5 bytes |         9 bits       | 0-32 bytes | 1-2 bytes |

Packet Control Field Format
| Payload |  PID   | NO_ACK |
| 6 bits  | 2 bits | 1 bit  |

The CRC is optional in the ShockBurst™ packet format and is controlled by the EN_CRC bit in the CONFIG register.
The 9 bit Packet Control Field is not present in the ShockBurst™ packet format

ShockBurst™ Packet Format
| Preamble |  Address  |  Payload   |   CRC     |
|  1 byte  | 3-5 bytes | 1-32 bytes | 1-2 bytes |
*/

#define PREAMBLE_LEN 1          // bytes

#define MIN_ADDRESS_LEN 3       // bytes                                
#define MAX_ADDRESS_LEN 5       // bytes

#define PACKET_CTRL_FIELD_LEN 9 // bits

#define ES_MIN_PAYLOAD_LEN 0    // bytes. ES is for Enhanced ShockBurst™
#define S_MIN_PAYLOAD_LEN 1     // bytes. S is for ShockBurst™          
#define MAX_PAYLOAD_LEN 32      // bytes

#define MIN_CRC_LEN 1 // bytes
#define MAX_CRC_LEN 2 // bytes

// Packet Control Field Format
#define PACKET_CTRL_FIELD_PAYLOAD_LEN 6 // bits                       
#define PACKET_CTRL_FIELD_PID_LEN 2     // bits. PID = Packet Identity
#define PACKET_CTRL_FIELD_NO_ACK_LEN 1  // bits

// This field is only used if the Dynamic Payload Length function is enabled
#define PACKET_CTRL_FIELD_PAYLOAD_EMPTY_ACK 0b000000 // only used in empty ACK packets        
#define PACKET_CTRL_FIELD_PAYLOAD_MAX_LEN 0b100000   // specifies a payload length of 32 bytes
#define PACKET_CTRL_FIELD_PAYLOAD_DONT_CARE 0b100001 // don't care about payload length

#define ES_PACKET_MIN_LEN (PREAMBLE_LEN + MIN_ADDRESS_LEN + MIN_PAYLOAD_LEN + MIN_CRC_LEN) * 8 + PACKET_CTRL_FIELD_LEN // bits
#define ES_PACKET_MAX_LEN (PREAMBLE_LEN + MAX_ADDRESS_LEN + MAX_PAYLOAD_LEN + MAX_CRC_LEN) * 8 + PACKET_CTRL_FIELD_LEN // bits
#define S_PACKET_MIN_LEN (PREAMBLE_LEN + MIN_ADDRESS_LEN + MIN_PAYLOAD_LEN + MIN_CRC_LEN) * 8                          // bits
#define S_PACKET_MAX_LEN (PREAMBLE_LEN + MAX_ADDRESS_LEN + MAX_PAYLOAD_LEN + MAX_CRC_LEN) * 8                          // bits
