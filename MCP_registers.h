//
// Created by simon on 8/05/2021.
//

#ifndef MCP_MCP_REGISTERS_H
#define MCP_MCP_REGISTERS_H

//SPI INSTRUCTION SIMULATIONS ------------------------------------------------------------------------------------------
#define 	SIM_RESET_MCP				0xC0	//1100 0000
#define 	SIM_READ				    0x03	//0000 0011
#define 	SIM_READ_RX_BUFFER_0_full	0x90	//1001 0000
#define 	SIM_READ_RX_BUFFER_0		0x92	//1001 0010
#define 	SIM_READ_RX_BUFFER_1_full	0x94	//1001 0100
#define 	SIM_READ_RX_BUFFER_1		0x96	//1001 0110
#define 	SIM_WRITE					0x02	//0000 0010
#define 	SIM_LOAD_TX_BUFFER_0_full	0x40	//0100 0000
#define 	SIM_LOAD_TX_BUFFER_0		0x41	//0100 0001
#define 	SIM_LOAD_TX_BUFFER_1_full	0x42	//0100 0010
#define 	SIM_LOAD_TX_BUFFER_1		0x43	//0100 0011
#define 	SIM_LOAD_TX_BUFFER_2_full	0x44	//0100 0100
#define 	SIM_LOAD_TX_BUFFER_2		0x45	//0100 0101
#define 	SIM_RTS_0					0x81	//1000 0001
#define 	SIM_RTS_1					0x82	//1000 0010
#define 	SIM_RTS_2					0x84	//1000 0100
#define 	SIM_READ_STATUS				0xA0	//1010 0000
#define 	SIM_RX_STATUS				0xB0	//1011 0000
#define 	SIM_BIT_MODIFY				0x05	//0000 0101

const static unsigned char MCP_spi_instructions[] = {SIM_RESET_MCP, SIM_READ, SIM_READ_RX_BUFFER_0_full, SIM_READ_RX_BUFFER_0, SIM_READ_RX_BUFFER_1_full, SIM_READ_RX_BUFFER_1, SIM_WRITE, SIM_LOAD_TX_BUFFER_0_full, SIM_LOAD_TX_BUFFER_0, SIM_LOAD_TX_BUFFER_1_full, SIM_LOAD_TX_BUFFER_1, SIM_LOAD_TX_BUFFER_2_full, SIM_LOAD_TX_BUFFER_2, SIM_RTS_0, SIM_RTS_1, SIM_RTS_2, SIM_READ_STATUS, SIM_RX_STATUS, SIM_BIT_MODIFY};
const static unsigned char MCP_spi_expected_writes[] = {0, 1, 0, 0, 0, 0, 2, 14, 8, 14, 8, 14, 8, 0, 0, 0, 0, 0, 3};
const static unsigned char MCP_spi_expected_reads[]  = {0, 1, 14, 8, 14, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0};

//REGISTER ADDRESSES --------------------------------------------------------------------
//TO DO : add all the names of the registers and their address

#define TXB0CTRL    0x30    //1
#define TXB1CTRL    0x40    //2
#define TXB2CTRL    0x50    //3
#define TXRTSCTRL   0x0D
#define TXB0SIDH    0x31    //5
#define TXB1SIDH    0x41
#define TXB2SIDH    0x51
#define TXB0SIDL    0x32
#define TXB1SIDL    0x42
#define TXB2SIDL    0x52    //10
#define TXB0EID8    0x33
#define TXB1EID8    0x43
#define TXB2EID8    0x53
#define TXB0EID0    0x34
#define TXB1EID0    0x44    //15
#define TXB2EID0    0x54
#define TXB0DLC     0x35
#define TXB1DLC     0x45
#define TXB2DLC     0x55
#define TXB0D0      0x36    //20
#define TXB0D1      0x37
#define TXB0D2      0x38
#define TXB0D3      0x39
#define TXB0D4      0x3A
#define TXB0D5      0x3B    //25
#define TXB0D6      0x3C
#define TXB0D7      0x3D
#define TXB1D0      0x46
#define TXB1D1      0x47
#define TXB1D2      0x48    //30
#define TXB1D3      0x49
#define TXB1D4      0x4A
#define TXB1D5      0x4B
#define TXB1D6      0x4C
#define TXB1D7      0x4D    //35
#define TXB2D0      0x56
#define TXB2D1      0x57
#define TXB2D2      0x58
#define TXB2D3      0x59
#define TXB2D4      0x5A    //40
#define TXB2D5      0x5B
#define TXB2D6      0x5C
#define TXB2D7      0x5D

#define RXB0CTRL    0x60
#define RXB1CTRL    0x70    //45
#define BFPCTRL     0x0C
#define RXB0SIDH    0X61
#define RXB1SIDH    0x71
#define RXB0SIDL    0x62
#define RXB1SIDL    0x72    //50
#define RXB0EID8    0x63
#define RXB1EID8    0x73
#define RXB0EID0    0x64
#define RXB1EID0    0x74
#define RXB0DLC     0x65    //55
#define RXB1DLC     0x75
#define RXB0D0      0x66
#define RXB0D1      0x67
#define RXB0D2      0x68
#define RXB0D3      0x69    //60
#define RXB0D4      0x6A
#define RXB0D5      0x6B
#define RXB0D6      0x6C
#define RXB0D7      0x6D
#define RXB1D0      0x76    //65
#define RXB1D1      0x77
#define RXB1D2      0x78
#define RXB1D3      0x79
#define RXB1D4      0x7A
#define RXB1D5      0x7B    //70
#define RXB1D6      0x7C
#define RXB1D7      0x7D

#define RXF0SIDH    0x00
#define RXF1SIDH    0x04
#define RXF2SIDH    0x08    //75
#define RXF3SIDH    0x10
#define RXF4SIDH    0x14
#define RXF5SIDH    0x18
#define RXF0SIDL    0x01
#define RXF1SIDL    0x05    //80
#define RXF2SIDL    0x09
#define RXF3SIDL    0x11
#define RXF4SIDL    0x15
#define RXF5SIDL    0x19
#define RXF0EID8    0x02    //85
#define RXF1EID8    0x06
#define RXF2EID8    0x0A
#define RXF3EID8    0x12
#define RXF4EID8    0x16
#define RXF5EID8    0x1A    //90
#define RXF0EID0    0x03
#define RXF1EID0    0x07
#define RXF2EID0    0x0B
#define RXF3EID0    0x13
#define RXF4EID0    0x17    //95
#define RXF5EID0    0x1B
#define RXM0SIDH    0x20
#define RXM1SIDH    0x24
#define RXM0SIDL    0x21
#define RXM1SIDL    0x25    //100
#define RXM0EID8    0x22
#define RXM1EID8    0x26
#define RXM0EID0    0x23
#define RXM1EID0    0x27

#define CNF1        0x2A    //105
#define CNF2        0x29
#define CNF3        0x28
#define TEC         0x1C
#define REC         0x1D
#define EFLG        0x2D    //110

#define CANINTE     0x2B
#define CANINTF     0x2C

#define CANCTRL     0x0F
#define CANSTAT     0x0E


const static unsigned char MCP_registers[] = {TXB0CTRL, TXB1CTRL, TXB2CTRL, TXRTSCTRL, TXB0SIDH, TXB1SIDH, TXB2SIDH, TXB0SIDL, TXB1SIDL, TXB2SIDL, TXB0EID8, TXB1EID8, TXB2EID8, TXB0EID0, TXB1EID0, TXB2EID0, TXB0DLC, TXB1DLC, TXB2DLC, TXB0D0, TXB0D1, TXB0D2, TXB0D3, TXB0D4, TXB0D5, TXB0D6, TXB0D7, TXB1D0, TXB1D1, TXB1D2, TXB1D3, TXB1D4, TXB1D5, TXB1D6, TXB1D7, TXB2D0, TXB2D1, TXB2D2, TXB2D3, TXB2D4, TXB2D5, TXB2D6, TXB2D7, RXB0CTRL, RXB1CTRL, BFPCTRL, RXB0SIDH, RXB1SIDH, RXB0SIDL, RXB1SIDL, RXB0EID8, RXB1EID8, RXB0EID0, RXB1EID0, RXB0DLC, RXB1DLC, RXB0D0, RXB0D1, RXB0D2, RXB0D3, RXB0D4, RXB0D5, RXB0D6, RXB0D7, RXB1D0, RXB1D1, RXB1D2, RXB1D3, RXB1D4, RXB1D5, RXB1D6, RXB1D7, RXF0SIDH, RXF1SIDH, RXF2SIDH, RXF3SIDH, RXF4SIDH, RXF5SIDH, RXF0SIDL, RXF1SIDL, RXF2SIDL, RXF3SIDL, RXF4SIDL, RXF5SIDL, RXF0EID8, RXF1EID8, RXF2EID8, RXF3EID8, RXF4EID8, RXF5EID8, RXF0EID0, RXF1EID0, RXF2EID0, RXF3EID0, RXF4EID0, RXF5EID0, RXM0SIDH, RXM1SIDH, RXM0SIDL, RXM1SIDL, RXM0EID8, RXM1EID8, RXM0EID0, RXM1EID0, CNF1, CNF2, CNF3, TEC, REC, EFLG, CANINTE, CANINTF, CANCTRL, CANSTAT};

#endif //MCP_MCP_REGISTERS_H
