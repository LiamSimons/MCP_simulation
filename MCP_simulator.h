//
// Created by simon on 5/7/2021.
//
/*
 * MCP_simulator : acts like the MCP, has variables for all registers that can be set
 *                 and read with the same functions used on the actual pic for spi comm
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "MCP_registers.h"

#ifndef MCP_MCP_SIMULATOR_H
#define MCP_MCP_SIMULATOR_H

//SIMULATION OF THE SLAVE SELECT OF THE PIC18F25K50 --------------------------------------------------------------------
typedef struct LATA {       //REMOVE THIS IN MPLAB
    unsigned char LATA4;    //REMOVE THIS IN MPLAB cs
    unsigned char LATA3;    //REMOVE THIS IN MPLAB stby
}LATA;                      //REMOVE THIS IN MPLAB
//REMOVE THIS IN MPLAB
struct LATA LATAbits;       //REMOVE THIS IN MPLAB

unsigned static char spi_write_count = 0;

//REGISTER MEMORY
const static unsigned char NR_REGISTERS = sizeof(MCP_registers);
const static unsigned char NR_COMMANDS = sizeof(MCP_spi_instructions);


//FUNCTIONS THAT SIMULATE THE READ AND WRITE SPI
void writeSPI(unsigned char data);
unsigned char readSPI(void);

//EXTRA FUNCTIONS
void MCP_startup();
signed char find_register_index(unsigned char address);
signed char find_command_index(unsigned char command);

//SPI INSTRUCTION SIMULATIONS
void SIM_reset();								//resets the device
uint8_t SIM_read(uint8_t address);				//read out a register of the mcp
void SIM_read_rx(char full, char nr);			//reads out the chosen receive buffer
void SIM_write(uint8_t address, uint8_t data);	//write data to a given register
void SIM_rts(char TXB);							//Request to Send for the chosen transmit buffer
uint8_t SIM_read_status();						//returns the status register
uint8_t SIM_rx_status();						//returns the rx register
void SIM_bit_modify(uint8_t address, uint8_t mask, uint8_t data);


#endif //MCP_MCP_SIMULATOR_H


/*
 * void writeSPI(uint8_t data){
        printf("ON SPI LINE: %d\n", data);
        return;
    }
    uint8_t readSPI(){
        printf("READ FROM SPI LINE\n");
        //TEST PHASE : init
        return 0x00;

        return 0;
    }
 */