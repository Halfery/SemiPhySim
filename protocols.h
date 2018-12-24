#pragma once

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;

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

///////////////////////////////////////////////////////////////
//AutoPilot state-switch instructions
//after autopilot initialization, autopilot sends R_BOOT_AUTOPILOT instruction.
//then autopilot switches in AUTOPILOT_IDLE state
//////////////////////////////////////////////////////////////////
#define CHECKOUT_AUTOPILOT_STATE			0x00
#define AUTOPILOT_IDLE						0x01
#define CHECKOUT_SUBSYS						0x02
#define CHECKOUT_HALF_ASSEM_SIMFLIGHT		0x03
#define CHECKOUT_SIMLAUNCH					0x04
#define CHECKOUT_ASSEM_ALL_SIMFLIGHT		0x05
#define CHECKOUT_LAUNCH_FIELD_SIMFLIGHT		0xA1
#define SEMI_PHY_SIMULATION					0xB1
#define EXITTO_AUTOPILOT_IDLE				0xFE
#define ROCKET_LAUNCH						0xD1

//////////////////////////////////////////////////////////////////////////
//IMU Instruction Set
//AutoPilot Sends(200Hz):
//IDs//NUM//0x00//
#define IMU_MEASURE_QUEST					0x81
#define IMU_SELFTEST_QUEST					0x71
#define IMU_SIM_DATA_UPLOAD_QUEST			0x01
#define IMU_SIM_DATA_UPLOAD_EXIT_QUEST		0x11
#define IMU_SIM_DATA_OUTPUT_QUEST			0xB1
#define IMU_SIM_DATA_OUTPUT_EXIT_QUEST		0xA1
#define IMU_SIM_DATA_ERASE_QUEST			0x91

//IMU Sends:
#define IMU_MEASURE_RESULT					0x82
#define IMU_SELFTEST_RESULT					0x72
#define IMU_SIM_DATA_UPLOAD_RESULT			0x02
#define IMU_SIM_DATA_UPLOAD_EXIT_RESULT		0x12
#define IMU_SIM_DATA_OUTPUT_RESULT			0xB2
#define IMU_SIM_DATA_OUTPUT_EXIT_RESULT		0xA2
#define IMU_SIM_DATA_ERASE_RESULT			0x92

typedef struct
{
	uint16_t frame_head = FRAME_HEAD;
	uint8_t frame_length = 0;
	uint8_t data[253];
	uint16_t crc_word = 0;
	uint16_t frame_end = FRAME_END;
} s_serial_Frame;

uint16_t rtn_crc_encode(uint8_t *data, uint8_t length);

class c_serial_protocol {
public:
	c_serial_protocol();
	~c_serial_protocol();
	void m_setFrame(uint8_t *data,uint8_t data_length);
private:
	s_serial_Frame serial_Frame;
	s_serial_Frame * p_serial_Frame;
};
/*
uint16_t m_crc16_table[256] = {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};
*/



