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
signed char find_register_index(unsigned char address_dummy);
signed char find_command_index(unsigned char command_dummy);
void execute_command(unsigned char command_dummy);

//DEBUGGING
void print_register_data();

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