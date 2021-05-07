//
// Created by simon on 5/7/2021.
//

#ifndef MCP_MCP_SIMULATOR_H
#define MCP_MCP_SIMULATOR_H

#endif //MCP_MCP_SIMULATOR_H

//FUNCTIONS THAT SIMULATE THE READ AND WRITE SPI
void writeSPI(unsigned char x);
unsigned char readSPI(void);
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