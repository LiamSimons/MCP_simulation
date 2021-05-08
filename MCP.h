//MCP header file ------------------------------------------------------------------------------------------------------

#include "MCP_simulator.h"  //REMOVE THIS IN MPLAB


#ifndef MCP_MCP_H
#define MCP_MCP_H


//INCLUDES -------------------------------------------------------------------------------------------------------------
//#include <xc.h>           //INCLUDE THIS IN MPLAB
//#include <stdio.h>        //INCLUDE THIS IN MPLAB
//#include <stdint.h>       //INCLUDE THIS IN MPLAB

//SPI INSTRUCTIONS -----------------------------------------------------------------------------------------------------
#define 	RESET_MCP				0xC0	//1100 0000
#define 	READ					0x03	//0000 0011
#define 	READ_RX_BUFFER_0_full	0x90	//1001 0000
#define 	READ_RX_BUFFER_0		0x92	//1001 0010
#define 	READ_RX_BUFFER_1_full	0x94	//1001 0100
#define 	READ_RX_BUFFER_1		0x96	//1001 0110
#define 	WRITE					0x02	//0000 0010
#define 	LOAD_TX_BUFFER_0_full	0x40	//0100 0000
#define 	LOAD_TX_BUFFER_0		0x41	//0100 0001
#define 	LOAD_TX_BUFFER_1_full	0x42	//0100 0010
#define 	LOAD_TX_BUFFER_1		0x43	//0100 0011
#define 	LOAD_TX_BUFFER_2_full	0x44	//0100 0100
#define 	LOAD_TX_BUFFER_2		0x45	//0100 0101
#define 	RTS_0					0x81	//1000 0001
#define 	RTS_1					0x82	//1000 0010
#define 	RTS_2					0x84	//1000 0100
#define 	READ_STATUS				0xA0	//1010 0000
#define 	RX_STATUS				0xB0	//1011 0000
#define 	BIT_MODIFY				0x05	//0000 0101


//STORAGE ON PIC TO STORE THE VALUES READ FROM THE RX BUFFER -----------------------------------------------------------
uint8_t RX_STORAGE[14];

//SPI FUNCTIONS --------------------------------------------------------------------------------------------------------
void MCP_reset();								//resets the device

uint8_t MCP_read(uint8_t address);				//read out a register of the mcp
//returns the read out register

void MCP_read_rx(char full, char nr);			//reads out the chosen receive buffer
//puts the values in the MCU storage
void MCP_write(uint8_t address, uint8_t data);	//write data to a given register

//void MCP_load_tx(bool full, char nr);			//for this i wouldn't use a function

void MCP_rts(char TXB);							//Request to Send for the chosen transmit buffer

uint8_t MCP_read_status();						//returns the status register

uint8_t MCP_rx_status();						//returns the rx register

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
//modifies the bits specified in the mask
//in the register of the address
//to the value of data


//MCP INITIALIZATION ---------------------------------------------------------------------------------------------------
void MCP_init();								//initializes all the needed registers of the mcp


//MCP MESSAGE TRANSMITION CODE -----------------------------------------------------------------------------------------
//SIDL = [SID2, SID1, SID0, 0, EXIDE, 0, EID1, EID0];
void MCP_send_message(char priority, uint8_t SIDH, uint8_t SIDL, char nr_bytes,
                      uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
                      uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7);			//send a message on the can bus

uint8_t check_available_tx_buffer();                //returns the number of the first available transmit buffer


//MCP MESSAGE RECEIVE CODE ---------------------------------------------------------------------------------------------
//use when interrupt generated -> int pin on pic not yet connected!!!
void MCP_read_buffer(uint8_t local_address);    //reads the buffers containing the received message
                                                //local_address = address on pic to store buffer contents


#endif //MCP_MCP_H
