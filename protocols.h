#pragma once

#define RTN_SUCCESS			0x00
#define RTN_BUSY			0x01

/////////////////////////////////////////////////////////////////////////////////
//frame assumption:
//frameHead//frameLength//dataSeg//CRC_byte//frameEnd//
//max dataSeg's length is 249Bytes.
/////////////////////////////////////////////////////////////////

#define FRAME_HEAD					0x5A54
#define FRAME_END					0x5AFE
#define MAX_FRAME_LENGTH			0xFF
#define CRC16_CCITT					0x11021

/////////////////////////////////////////////////////////////////////
//top instructions IDs in dataSeg
//Supervisor instructions 
#define A_SELFCHECK					0x02
#define R_SELFCHECK					0x01
#define A_AUTOPILOT_VER				0x12
#define R_AUTOPILOT_VER				0x11
#define A_ERASE_AUTOPILOT			0x22
#define R_ERASE_AUTOPILOT			0x21
#define A_UPLOAD_AUTOPILOT_START	0x32
#define R_UPLOAD_AUTOPILOT_START	0x31
#define A_UPLOAD_AUTOPILOT_OVER		0x52
#define R_UPLOAD_AUTOPILOT_OVER		0x51
#define A_FLASH_AUTOPILOT			0x62
#define R_FLASH_AUTOPILOT			0x61
#define A_DOWNLOAD_AUTOPILOT_START	0x72
#define R_DOWNLOAD_AUTOPILOT_START	0x71
#define A_DOWNLOAD_AUTOPILOT_OVER	0x91
#define R_DOWNLOAD_AUTOPILOT_OVER	0x92
#define A_LOAD_AUTOPILOT			0xA2
#define R_LOAD_AUTOPILOT			0xA1
#define A_BOOT_AUTOPILOT			0xB2
#define R_BOOT_AUTOPILOT			0xB1
//AutoPilot state-machine-switch instructions
#define A_SET_AUTOPILOT_STATE		0xEE
#define R_SET_AUTOPILOT_STATE		0xEF
//top instructions IDs end
/////////////////////////////////////////////////////////////////////////

