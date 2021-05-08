//
// Created by Liam Simons on 5/7/2021.
//

#include "MCP_simulator.h"

unsigned char MCP_registers_data[114];

unsigned char command;
unsigned char writes_to_go = 0;
unsigned char reads_to_go = 0;
unsigned char address;
unsigned char mask;

void writeSPI(unsigned char data){
    //check what the address is - when bytes_to_come==0 it is a command
    //check which command to know how many bytes to come
    //make a function for each spi command
    if(writes_to_go == 0){
        command = data;
        signed char index_dummy = find_command_index(command);
        if(index_dummy == -1) {
            reads_to_go = 0;
            writes_to_go = 0;
            return;
        }
        writes_to_go = MCP_spi_expected_writes[index_dummy];
        reads_to_go = MCP_spi_expected_reads[index_dummy];
    }
    else{
        signed char index_dummy = find_command_index(command);
        if(index_dummy == -1) return;
        if(writes_to_go == MCP_spi_expected_writes[index_dummy]){
            if(find_register_index(data) == -1) {
                reads_to_go = 0;
                writes_to_go = 0;
                return;
            }
            address = data;
            writes_to_go--;
        } else{
            if(command != SIM_BIT_MODIFY) {
                unsigned char register_address_dummy = find_register_index(address);
                if (register_address_dummy == -1) return;
                MCP_registers_data[register_address_dummy] = data;
                writes_to_go--;
                if(writes_to_go != 0){
                    address++;
                }
            } else{
                if(writes_to_go == 2){
                    mask = data;
                    writes_to_go--;
                } else{
                    signed char register_index_dummy = find_register_index(address);
                    if(register_index_dummy == -1) return;
                    MCP_registers_data[register_index_dummy] = data;
                    writes_to_go--;
                }
            }
        }
    }
}
unsigned char readSPI(void){
    if(reads_to_go != 0) {
        return MCP_registers_data[address];
    }
}

signed char find_register_index(unsigned char address_dummy){
    signed char index = 0;
    for(unsigned char i = 0; i < NR_REGISTERS; i++){
        if(address_dummy == MCP_registers[i]){
            return index;
        }
        index++;
    }
    return -1;
}

signed char find_command_index(unsigned char command_dummy){
    signed char index = 0;
    for(unsigned char i = 0; i < NR_COMMANDS; i++){
        if(command_dummy == MCP_spi_instructions[i]){
            return index;
        }
        index++;
    }
    return -1;
}





//SPI INSTRUCTION SIMULATIONS
void SIM_reset();								//resets the device
uint8_t SIM_read(uint8_t address);				//read out a register of the mcp
void SIM_read_rx(char full, char nr);			//reads out the chosen receive buffer
void SIM_write(uint8_t address, uint8_t data);	//write data to a given register
void SIM_rts(char TXB);							//Request to Send for the chosen transmit buffer
uint8_t SIM_read_status();						//returns the status register
uint8_t SIM_rx_status();						//returns the rx register
void SIM_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

//STARTUP FUNCTIONS TO INITIALIZE FACTORY DEFAULT OF THE MCP
void MCP_startup(){
    writes_to_go = 0;
    reads_to_go = 0;
    for(unsigned char i = 0; i<NR_REGISTERS; i++){
        MCP_registers_data[i] = 0x00;
    }
}