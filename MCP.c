/*
 * WARNING - all LATAbits.RA4 commands are commented out - to use on pic uncomment these
 *         - also delete the empty SPI_write and SPI_read functions from this and the header file
 *         - import the other files for the implementation of these 2 functions
 *         - remove all TEST PHASE parts with the line of code below it
 * */

//MCP SOURCE -----------------------------------------------------------------------------------------------------------
#include "MCP.h"

//SPI FUNCTIONS --------------------------------------------------------------------------------------------------------
void MCP_Reset(){
    LATAbits.LATA4 = 0;			//start comm by pulling cs low
    writeSPI(RESET_MCP);		//write the reset command on the spi line
    LATAbits.LATA4 = 1;			//end comm by making cs high again
}

uint8_t MCP_read(uint8_t address){
    uint8_t value = 0;			//dummy to store value coming from spi
    LATAbits.LATA4 = 0;			//start comm by pulling cs low
    writeSPI(READ);			    //write the read command on the spi line
    writeSPI(address);			//write the address to read from on the spi line
    value = readSPI();			//read the value from the ssp buffer
    LATAbits.LATA4 = 1;			//end comm by making cs high again
    return value;				//return the value
}

void MCP_read_rx(char full, char nr) {				//full(starting form SIDH or from D0)
    uint8_t command = 0;
    int amount = 0;
    //Check which command to use
    if(nr == 0) {
        if(full == 1){
            command = READ_RX_BUFFER_0_full;
            amount = 14;
        }
        else{
            command = READ_RX_BUFFER_0;
            amount = 8;
        }
    }
    if(nr == 1){
        if(full == 1){
            command = READ_RX_BUFFER_1_full;
            amount = 14;
        }
        else{
            command = READ_RX_BUFFER_1;
            amount = 8;
        }
    }
//    LATAbits.LATA4 = 0;		//start comm
    writeSPI(command);			//write the command for the right buffer and where to start from
    for(unsigned int i = (sizeof(RX_STORAGE)-amount); i==sizeof(RX_STORAGE); i++){
        RX_STORAGE[i] = readSPI();
    }
    LATAbits.LATA4 = 1;			//end comm
}

void MCP_write(uint8_t address, uint8_t data){
    LATAbits.LATA4 = 0;			//start comm
    writeSPI(WRITE);            //write the WRITE command on the spi line
    writeSPI(address);			//write address on spi line
    writeSPI(data);			    //write data for that address on spi line
    LATAbits.LATA4 = 1;			//end comm
}

//void MCP_load_tx(bool full, char nr);			//hiervoor zou ik geen functie gebruiken


void MCP_rts(char TXB){
    //Determine which TXB buffer to set to ready to send
    uint8_t command = 0;
    if(TXB == 0){
        command = RTS_0;
    }
    if(TXB == 1){
        command = RTS_1;
    }
    if(TXB == 2){
        command = RTS_2;
    }
    LATAbits.LATA4 = 0;			//start comm
    writeSPI(command);			//write rts command to spi line
    LATAbits.LATA4 = 1;			//end comm
}

uint8_t MCP_read_status(){
    uint8_t status = 0;			//dummy to store the status bits
    LATAbits.LATA4 = 0;			//start comm
    writeSPI(READ_STATUS);		//write read status command to spi line
    status = readSPI();		    //store value read from spi line
    LATAbits.LATA4 = 1;			//stop comm
    return status;				//return value
}

uint8_t MCP_rx_status(){
    uint8_t status = 0;			//dummy to store the status bits
    LATAbits.LATA4 = 0;			//start comm
    writeSPI(RX_STATUS);		//write rx status command to spi line
    status = readSPI();		    //store value read from spi line
    LATAbits.LATA4 = 1;			//stop comm
    return status;				//return value
}

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
    LATAbits.LATA4 = 0;			//start comm
    writeSPI(BIT_MODIFY);		//write bit modify command to spi line
    writeSPI(address);			//write address of the byte
    writeSPI(mask);			    //write which bits of the byte have to change to the spi line
    writeSPI(data);			    //write the values of those bits to the spi line
    LATAbits.LATA4 = 1;			//stop comm
}



//MCP INITIALIZATION ---------------------------------------------------------------------------------------------------
//The mcp can controller starts up in configuration mode
void MCP_init(){
    //Transceiver
    LATAbits.LATA3 = 1;			//RA3 is connected to STBY - transceiver goes in standby when this is high

    //4.1 Message transmit registers
    //I think we only need to set these registers every time we send a message

    //4.2 Message receive registers
    MCP_bit_modify(0x60, 0x04, 0x04);		//Register 4-9
    //adress=0x60 (RXB0CTRL) ; mask=0x04(bit[2]) ; data=0x04(set bit[2] to 1)
    //bit[2] = BUKT bit = rollover enabled
    //Register 4-10 : default ok

    //4.3 Acceptance filter registers
    //RXB1 Filters :
    //Register 4-18 : 6 standard identifier high registers	//RXFxSIDH
    MCP_write(0x00, 0x00);					//TO DO : What will be our SID
    MCP_write(0x04, 0x00);					//TO DO : What will be our SID
    MCP_write(0x08, 0x00);					//TO DO : What will be our SID
    MCP_write(0x10, 0x00);					//TO DO : What will be our SID
    MCP_write(0x14, 0x00);					//TO DO : What will be our SID
    MCP_write(0x18, 0x00);					//TO DO : What will be our SID
    //Register 4-19 : SID + EXIDE + EID						//RXFxSIDL
    MCP_write(0x01, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x05, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x09, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x11, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x15, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x19, 0x00);					//TO DO : What will be our SID and EID

    //RXB0 Masks :
    //Register 4-22 : 2 standard mask high registers		//RXMxSIDH
    MCP_write(0x20, 0x00);					//TO DO : What will be our SID mask
    MCP_write(0x24, 0x00);					//TO DO : What will be our SID mask
    //Register 4-23 : SID + EXIDE + EID						//RXMxSIDL
    MCP_write(0x21, 0x00);					//TO DO : What will be our SID and EID
    MCP_write(0x25, 0x00);					//TO DO : What will be our SID and EID


    //4.4 Bit time configuration registers
    //CNF1 - Register 4-26
    MCP_write(0x2A, 0xC7);					//SJW[7:6] = 4Tq =11
    //BRP[5:0] = 16Tosc = 2*(7+1)/Fosc = 000111
    //1100 0111 = C7
    //CNF2 - Register 4-27
    MCP_write(0x29, 0xD2);					//BTLMODE[7] = 1(length PS2 determined by PHSEG[2:0] bits of CNF3)
    //SAM[6] = 1(Bus line is sampled 3 times at the sample point)
    //PHSEG1[2:0] = 010( (PS1=PHSEG1+1)*Tq -> 3Tq)
    //CNF3 - Register 4-28
    MCP_write(0x28, 0x02);					//SOF[7] = 0 (denk ik)
    //WAKFIL[6] = 0 (hebben we ni nodig denk ik)
    //UI[5-3] = 000
    //PHSEG2[2:0] = 010

    //4.5 Error detection registers
    //only needed out of config

    //4.6 Interrupt registers
    MCP_write(0x2B, 0xFF);					// this enables all interrupts

    //4.7 CAN control registers
    /*if((MCP_read(0x0E)&0xE0) != 8){
        while(1){
            LATCbits.LC1=1;
            LATCbits.LC2=1;
            __delay_ms(500);
            LATCbits.LC1=0;
            LATCbits.LC2=0;
            __delay_ms(500);
        }
    }*/
    while((MCP_read(0x0E)&0xE0) == 8){		//read CANSTAT.OPMOD - first 3 bits of the register : 000 = normal mode
        MCP_write(0x0F, 0x00);			//put controller into normal mode
    }										        //p7 : requested mode must be verified by reading the OPMOD bits in the CANSTAT register
}



//MCP MESSAGE TRANSMITION CODE -----------------------------------------------------------------------------------------
//I would say we only use 1 buffer to send messages?
//ESP sends message to sensor devices - they get interrupt and send message back
void MCP_send_message(char priority, uint8_t SIDH, uint8_t SIDL, char nr_bytes,
                      uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
                      uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7){
    //determine which buffer to use
    char buffer_nr = check_available_tx_buffer(); // = check_buffer;

    //set the priority in register 4-1
    uint8_t TXBxCTRL = 0x00;
    TXBxCTRL += priority;

    //Data length code bits register 4-7
    uint8_t TXBxDLC = 0x00;
    TXBxDLC += nr_bytes;

    //data array
    uint8_t data[] = {byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7};

    if(buffer_nr == 0){
        //register 4-1
        MCP_write(0x30, TXBxCTRL);        //last 2 bits are priority 11=highest;10=high_inter;01=low_inter;00= low
        //register 4-2 -> pins are not used
        //register 4-3
        MCP_write(0x31, SIDH);
        //register 4-4
        MCP_write(0x32, SIDL);
        //register 4-5 -> i don't think the extended identifier is necessary
        //register 4-6 -> same
        //register 4-7
        MCP_write(0x35, TXBxDLC);
        //register 4-8
        for(int i=0; i<nr_bytes; i++){
            MCP_write(0x36+i, data[i]);
        }
    }
    if(buffer_nr == 1){
        //register 4-1
        MCP_write(0x40, TXBxCTRL);        //last 2 bits are priority 11=highest;10=high_inter;01=low_inter;00= low
        //register 4-2 -> pins are not used
        //register 4-3
        MCP_write(0x41, SIDH);
        //register 4-4
        MCP_write(0x42, SIDL);
        //register 4-5 -> i don't think the extended identifier is necessary
        //register 4-6 -> same
        //register 4-7
        MCP_write(0x45, TXBxDLC);
        //register 4-8
        for(int i=0; i<nr_bytes; i++){
            MCP_write(0x46+i, data[i]);
        }
    }
    if(buffer_nr == 2){
        //register 4-1
        MCP_write(0x50, TXBxCTRL);        //last 2 bits are priority 11=highest;10=high_inter;01=low_inter;00= low
        //register 4-2 -> pins are not used
        //register 4-3
        MCP_write(0x51, SIDH);
        //register 4-4
        MCP_write(0x52, SIDL);
        //register 4-5 -> i don't think the extended identifier is necessary
        //register 4-6 -> same
        //register 4-7
        MCP_write(0x55, TXBxDLC);
        //register 4-8
        for(int i=0; i<nr_bytes; i++){
            MCP_write(0x56+i, data[i]);
        }
    }
    //RTS
    MCP_rts(buffer_nr);
}

uint8_t check_available_tx_buffer(){
    uint8_t buffer_nr = 99;
    if((MCP_read(0x30)&0x08)==0){
        buffer_nr = 0;
    } else{
        if((MCP_read(0x40)&0x08)==0){
            buffer_nr = 1;
        } else{
            if((MCP_read(0x50)&0x08)==0){
                buffer_nr = 2;
            }
        }
    }
    return buffer_nr;
}

//MCP MESSAGE RECEIVE CODE ---------------------------------------------------------------------------------------------
void MCP_read_buffer(uint8_t local_address){
    //TO DO : write function that checks 4-9 and 4-10 to see which filter enabled reception
    //register 4-9 - RXB0CTRL
    //not needed to change when receiving a message, only at init
    //register 4-10
    //same as 4-9
    //register 4-11
    //pins not used
    //register 4-12
    //SIDH already set in init
    //register 4-13
    //SIDL already set in init
    //register 4-14
    //EID8 already set in init
    //register 4-15
    //EID0 already set in init
    //register 4-16 & 4-17 - Data length code register
    uint8_t nr_bytes = 0;
    nr_bytes = MCP_read(0x65);
    if(nr_bytes != 0){
        MCP_read_rx(0, 0);
    }
    nr_bytes = MCP_read(0x75);
    if(nr_bytes != 0){
        MCP_read_rx(0, 1);
    }
}

//MAIN -----------------------------------------------------------------------------------------------------------------
int main(){                 //REMOVE THIS IN MPLAB
    MCP_startup();
    /*
    MCP_write(0x99, 0xFF);
    MCP_write(0x30, 0XFF);
    MCP_write(0x69, 0x45);
    signed char x = find_register_index(0x30);
    */
    for(unsigned char i = 0x00; i<NR_REGISTERS; i++) {
        unsigned int value = MCP_read(i);
        printf("REGISTER %i = %d\n", i+1, value);
    }

    /*
    MCP_init();             //REMOVE THIS IN MPLAB
    printf("\n");   //REMOVE THIS IN MPLAB
    MCP_send_message(0, 0x00, 0, 8,              //REMOVE THIS IN MPLAB
                     0x00, 0x00, 0x00, 0x00,       //REMOVE THIS IN MPLAB
                     0x00, 0x00, 0x00, 0x00);      //REMOVE THIS IN MPLAB*/

}
