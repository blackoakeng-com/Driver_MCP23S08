/*
 * File:   MCP23S08.c 
 * Driver source file for Microchip MCP23S08
 *   SPI 8-chan IO expander
 * Version 0.1
 * Author:  M Hoyt
 * Company: Black Oak Engineering
 *   blackoakeng.com - New York USA
 * Developed and tested on BlueJay v1.3 platform
 *   + custom Shield with 7 MCP23S08 chips.
 * Copyright 2023 - All Rights Reserved
 * License: License_BOE_MIT.txt included herewith.
 * All information herein from Microchip 2019 datasheet.
 * This source code is not intended for life support 
 * functions. No warranty is made as to its suitability 
 * for any particular application. 
 *

// Write sequence: /CS = L, MCP23S08_DeviceOpcode_Wr, Register, Datum Out byte, in sequential mode addr ptr incrs, repeat..., /CS = H
// Read sequence: /CS = L, MCP23S08_DeviceOpcode_Rd, Register, Datum In byte, in sequential mode addr ptr incrs, repeat..., /CS = H

#include <xc.h>
#include "BlueJay.h"
#include "MCP23S08.h"
#include "Spi.h"
#include "DigitalIO.h"
#include "Timers.h"

void mcp23s08_ResetAll(void)  // TODO May need intermediary passthrough in Utility
{
    IO_Reset_n = 0;
    delay_us(5);    // DS Param #30 = 1 us
    IO_Reset_n = 1;
}

void mcp23s08_DeselectAll(void)  // TODO May need intermediary passthrough in Utility
{
    IO_XP1_4_CS_n = IO_XP5_8_CS_n = IO_XP9_12_CS_n = IO_XP13_16_CS_n = 1;
    IO_Rly1_6_CS_n = IO_Rly7_12_CS_n = IO_Rly13_18_CS_n = 1;
    IO_LED1_4_CS_n = IO_LED5_8_CS_n = IO_LED9_12_CS_n = IO_LED13_16_CS_n = 1;    
    
}

SYS_RtnCode mcp23s08_InitAll(void)
{   
    SYS_RtnCode retVal = RTN_Executed;
    mcp23s08_DeselectAll();     
    if ((retVal = mcp23s08_Init(MCP23S08_UserKey1_8)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_UserKey9_16)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_UserKey17_24)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_UserKey25_32)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_Alarm1_8)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_Alarm9_16)) != RTN_Executed) return retVal;
    if ((retVal = mcp23s08_Init(MCP23S08_Alarm17_24)) != RTN_Executed) return retVal;
    return retVal;
}

// Init the 7 MCP23S08 chips individually. Call at startup in Utility.
// For now all are set up as simple IO buffers per schematic.
SYS_RtnCode mcp23s08_Init(uint8_t _mcp23s08_Handle)
{
    uint8_t datum = 0x00;
    SYS_RtnCode retVal = RTN_Executed;
    mcp23s08_DeselectAll();
    switch (_mcp23s08_Handle)
    {
        case MCP23S08_UserKey1_8:
            IO_UserKey1_8_CS_n = 0;		// Chip select
            datum = 0xFF;      // Per schematic, all inputs
            break;
        case MCP23S08_UserKey9_16:
            IO_UserKey9_16_CS_n = 0;
            datum = 0xFF;      
            break;
        case MCP23S08_UserKey17_24:
			IO_UserKey17_24_CS_n = 0;
            datum = 0xFF;            
            break;
        case MCP23S08_UserKey25_32:
            IO_UserKey25_32_CS_n = 0;
            datum = 0xFF;      
            break;             
        case MCP23S08_Alarm1_8:
            IO_Alarm1_8_CS_n = 0;
            datum = 0x00;      // Per schematic, all outs
            break;     
        case MCP23S08_Alarm9_16:
            IO_Alarm9_16_CS_n = 0;
            datum = 0x00;      
            break;  
        case MCP23S08_Alarm17_24:
            IO_Alarm17_24_CS_n = 0;
            datum = 0x00;      
            break;   
        default:
            retVal = RTN_ParmOutOfRange;      
    }
    spi1ByteExchange(MCP23S08_DeviceOpcode_Wr);
    spi1ByteExchange(MCP23S08_IODIR);
    spi1ByteExchange(datum);      
//    _spi1ByteExchange(MCP23S08_IPOL_DEFAULT);    // Autoincr...        
//    _spi1ByteExchange(MCP23S08_GPINTEN_DEFAULT);       
//    _spi1ByteExchange(MCP23S08_DEFVAL_DEFAULT);
//    _spi1ByteExchange(MCP23S08_INTCON_DEFAULT);
//    _spi1ByteExchange(MCP23S08_IOCON_DEFAULT);
//    _spi1ByteExchange(MCP23S08_GPPU_DEFAULT);
//    _spi1ByteExchange(MCP23S08_INTF_DEFAULT);
//    _spi1ByteExchange(MCP23S08_INTCAP_DEFAULT);
//    _spi1ByteExchange(MCP23S08_GPIO_DEFAULT);
//    _spi1ByteExchange(MCP23S08_OLAT_DEFAULT);    
    mcp23s08_DeselectAll();  
    return retVal;   
}

