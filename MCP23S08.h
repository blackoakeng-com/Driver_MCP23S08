/*
 * File:   MCP23S08.h 
 * Driver header file for Microchip MCP23S08
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

#ifndef MCP23S08_H
#define	MCP23S08_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum
{
    MCP23S08_UserKey1_8 = 1,
    MCP23S08_UserKey9_16,
    MCP23S08_UserKey17_24,
    MCP23S08_UserKey25_32,
    MCP23S08_Alarm1_8,
    MCP23S08_Alarm9_16,
    MCP23S08_Alarm17_24
} MCP23S08_Handle;    
    
    
#define MCP23S08_DeviceOpcode_Wr   0x40    // This due to strapping on PCB and to intrinsic address
#define MCP23S08_DeviceOpcode_Rd   0x41
    
    // Registers & default vals
#define MCP23S08_IODIR      0x00    // Set per schematic
#define MCP23S08_IPOL       0x01    // Bit read polarities. Do not change.
#define MCP23S08_IPOL_DEFAULT   0x00
#define MCP23S08_GPINTEN    0x02    // Interrupt on change. Future use.
#define MCP23S08_GPINTEN_DEFAULT   0x00    
#define MCP23S08_DEFVAL     0x03    // Default compare mask for Int on Change.
#define MCP23S08_DEFVAL_DEFAULT   0x00   
#define MCP23S08_INTCON     0x04    // Interrupt enable mask 
#define MCP23S08_INTCON_DEFAULT   0x00     
#define MCP23S08_IOCON      0x05    // Configuration
#define MCP23S08_IOCON_DEFAULT   0x10 
#define MCP23S08_IOCON_BYTEMODE  0x20
    // 5: SEQOP = 1, disable sequential operation.  Address Pointer does not incr.
    // 4: DISSLW = 0, slew rate enabled.
    // 3: HAEN = 0, disable address pins.
    // 2: ODR = 0, INT pins are active drivers, not open drain.
    // 1: INTPOL = 0, INT polarity is AL.
    // NET = 0x10
#define MCP23S08_GPPU       0x06    // Enables pullups on input pins. Set to 0x00.
#define MCP23S08_GPPU_DEFAULT   0x00     
#define MCP23S08_INTF       0x07    // Image of enabled interrupt pins.  Read only.
#define MCP23S08_INTF_DEFAULT   0x00     
#define MCP23S08_INTCAP     0x08    // Capture input value of input pin at interrupt.  Read only.
#define MCP23S08_INTCAP_DEFAULT   0x00     
#define MCP23S08_GPIO       0x09    // Read gives insta val of pin.  Write is to OLAT latch.      
#define MCP23S08_GPIO_DEFAULT   0x00      
#define MCP23S08_OLAT       0x0A    // Output latch. Read is from latch, not pin.
#define MCP23S08_OLAT_DEFAULT   0x00  
    
void mcp23s08_DeselectAll(void);   
void mcp23s08_ResetAll(void);    
SYS_RtnCode mcp23s08_InitAll(void);
SYS_RtnCode mcp23s08_Init(uint8_t chipHandle);
SYS_RtnCode mcp23s08_ByteModeSet(uint8_t mcp23s08_Handle, bool ByteModeOrSeq);
SYS_RtnCode mcp23s08_Exchange(uint8_t mcp23s08_Handle, uint8_t byWrite, uint8_t *byRead);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP23S08_H */
