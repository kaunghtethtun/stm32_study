/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(?) COPYLEFT 2024		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_LSDB4830_CAFC_H
#define __ROM_LSDB4830_CAFC_H

#include "stm32f4xx_hal.h"
#include "main.h"

#define RIGHT_MOTOR 0x601
#define LEFT_MOTOR 	0x602

//#define POSITION_MODE_ON 1
#define BASIC_MODE_ON 1

#ifdef POSITION_MODE_ON
/* POSITION MODE */
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Operation mode
  *  Attribute = 08S,RW
  *     Unit   = [DEC]
  *  Operation mode
  * 	-3 Speed mode without Acc/Dec
  * 	1 Position mode
  * 	3 Speed mode with Acc/Dec
  *	  4 Torque mode
  */

#define OPERATION_MODE							0x606000
#define OPERATION_MODE_1ST_BYTE			0x60
#define OPERATION_MODE_2ND_BYTE			0x60
#define OPERATION_MODE_3RD_BYTE			0x00
#define SPEED_WITH_ACCEL_DECEL_MODE	3
#define SPEED_MODE									-3
#define TORQUE_MODE									4
#define POSITION_MODE								1
#define UART_OPERATION_MODE					0x7017
#define UART_OPERATION_MODE_H					0x70
#define UART_OPERATION_MODE_L					0x17
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Control Word
  *  Attribute = 16S,RW
  *     Unit   = [HEX]
  */

#define CONTROL_WORD								0x604000
#define CONTROL_WORD_1ST_BYTE				0x40
#define CONTROL_WORD_2ND_BYTE				0x60
#define CONTROL_WORD_3RD_BYTE				0x00
#define CONTROL_WORD_ENABLE					0x0F
#define CONTROL_WORD_DISABLE				0x06
#define CONTROL_WORKD_CLEAR					0x86
#define UART_CONTROL_WORD						0x7019
#define UART_CONTROL_WORD_H					0x70
#define UART_CONTROL_WORD_L					0x19
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Current Operation mode
  *  Attribute = 8S,RO
  *     Unit   = [DEC]
  */

#define CURRENT_OP_MODE							0x606100
#define CURRENT_OP_MODE_1ST_BYTE		0x61
#define CURRENT_OP_MODE_2ND_BYTE		0x60
#define CURRENT_OP_MODE_3RD_BYTE	  0x00
#define UART_CURRENT_OP_MODE 				0x7018
#define UART_CURRENT_OP_MODE_H 			0x70
#define UART_CURRENT_OP_MODE_L 		  0x18
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Driver status word
  *  Attribute = 16U,RO
  *     Unit   = [HEX]
  */

#define DRIVER_STATUS								0x604100
#define DRIVER_STATUS_1ST_BYTE			0x41
#define DRIVER_STATUS_2ND_BYTE			0x60
#define DRIVER_STATUS_3RD_BYTE			0x00
#define DRIVER_STATUS_NORMAL				0x0000
#define DRIVER_STATUS_ERROR					0x0008
#define UART_DRIVER_STATUS 					0x7001
#define UART_DRIVER_STATUS_H 				0x70
#define UART_DRIVER_STATUS_L 				0x01
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Emergency Stop
  *  Attribute = 08U,RW
  *     Unit   = [DEC]
  */

#define EMERGENCY_STOP							0x605A11
#define EMERGENCY_STOP_1ST_BYTE			0x5A
#define EMERGENCY_STOP_2ND_BYTE			0x60
#define EMERGENCY_STOP_3RD_BYTE			0x11
#define EMERGENCY_STOP_ENABLE				1
#define EMERGENCY_STOP_DISABLE			0
#define UART_EMERGENCY_STOP					0x701F
#define UART_EMERGENCY_STOP_H				0x70
#define UART_EMERGENCY_STOP_L				0x1F
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target position in absolute positioning ( Valid in operation mode 1 )
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define ABSOLUTE_TARGET_POSITION		0x607A00
#define ABSOLUTE_TARGET_POSITION_1	0x7A
#define ABSOLUTE_TARGET_POSITION_2	0x60
#define ABSOLUTE_TARGET_POSITION_3	0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target position in relative positioning ( Valid in operation mode 1 )
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define RELATIVE_TARGET_POSITION		0x607B00
#define RELATIVE_TARGET_POSITION_1	0x7B
#define RELATIVE_TARGET_POSITION_2	0x60
#define RELATIVE_TARGET_POSITION_3	0x00
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Profile velocity_rpm ( Target speed in operation mode 1 )
  * Note -> This object will affect the value of object [ 0x7098 ]
  *  Attribute = 16U,RW, S5
  *     Unit   = [rpm]
  */

#define VELOCITY_RPM								0x608200
#define VELOCITY_RPM_1ST_BYTE				0x82
#define VELOCITY_RPM_2ND_BYTE				0x60
#define VELOCITY_RPM_3RD_BYTE				0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Acceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * 5
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define ACCELERATION								0x608300
#define ACCELERATION_1ST_BYTE				0x83
#define ACCELERATION_2ND_BYTE				0x60
#define ACCELERATION_3RD_BYTE				0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * 5
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION								0x608400
#define DECELERATION_1ST_BYTE				0x84
#define DECELERATION_2ND_BYTE				0x60
#define DECELERATION_3RD_BYTE				0x00
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration in emergency stop
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * 5
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION_IN_EMERGENCY		0x605A01
#define DECELERATION_IN_EMERGENCY_1	0x5A
#define DECELERATION_IN_EMERGENCY_2	0x60
#define DECELERATION_IN_EMERGENCY_3	0x01
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Following error window
  *  Only valid in mode 1 when Kpp0 is not 0
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define FOLLOWING_ERR_WINDOW				0x606500
#define FOLLOWING_ERR_WINDOW				0x65
#define FOLLOWING_ERR_WINDOW				0x60
#define FOLLOWING_ERR_WINDOW				0x00
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Position loop speed feedforward
  *  Only valid in mode 1
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define POS_LOOP_SPEED_FF						0x60FB02
#define POS_LOOP_SPEED_FF_1					0xFB
#define POS_LOOP_SPEED_FF_2					0x60
#define POS_LOOP_SPEED_FF_3					0x02

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kpp0, propotion gain 0 in position loop
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_POS				0x60FB01
#define PROPOTION_GAIN_IN_POS_1			0xFB
#define PROPOTION_GAIN_IN_POS_2			0x60
#define PROPOTION_GAIN_IN_POS_3			0x01

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvp0,propotion gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_SPEED			0x60F901
#define PROPOTION_GAIN_IN_SPEED_1		0xF9
#define PROPOTION_GAIN_IN_SPEED_2		0x60
#define PROPOTION_GAIN_IN_SPEED_3		0x01

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvi0,integrator gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define INTEGRATOR_GAIN_IN_SPEED		0x60F902
#define INTEGRATOR_GAIN_IN_SPEED_1	0xF9
#define INTEGRATOR_GAIN_IN_SPEED_2	0x60
#define INTEGRATOR_GAIN_IN_SPEED_3	0x02
#else 
/* SPEED MODE */
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Operation mode
  *  Attribute = 08S,RW,S5
  *     Unit   = [DEC]
  *  Operation mode
  * 	-3 Speed mode without Acc/Dec
  * 	1 Position mode
  * 	3 Speed mode with Acc/Dec
  *		4 Torque mode
  */

#define OPERATION_MODE							0x606000
#define OPERATION_MODE_1ST_BYTE			0x60
#define OPERATION_MODE_2ND_BYTE			0x60
#define OPERATION_MODE_3RD_BYTE			0x00
#define SPEED_MODE_WITH_ACCEL_DECEL	3
#define SPEED_MODE									-3
#define TORQUE_MODE									4
#define POSITION_MODE								1
#define UART_OPERATION_MODE					0x7017
#define UART_OPERATION_MODE_H				0x70
#define UART_OPERATION_MODE_L				0x17
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Control Word
  *  Attribute = 16S,RW
  *     Unit   = [HEX]
  */

#define CONTROL_WORD								0x604000
#define CONTROL_WORD_1ST_BYTE				0x40
#define CONTROL_WORD_2ND_BYTE				0x60
#define CONTROL_WORD_3RD_BYTE				0x00
#define CONTROL_WORD_ENABLE					(int16_t)0x0F
#define CONTROL_WORD_DISABLE				(int16_t)0x06
#define CONTROL_WORD_CLEAR					(int16_t)0x86
#define UART_CONTROL_WORD						0x7019
#define UART_CONTROL_WORD_H					0x70
#define UART_CONTROL_WORD_L					0x19
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Current Operation mode
  *  Attribute = 8S,RO
  *     Unit   = [DEC]
  */

#define CURRENT_OP_MODE							0x606100
#define CURRENT_OP_MODE_1ST_BYTE		0x61
#define CURRENT_OP_MODE_2ND_BYTE		0x60
#define CURRENT_OP_MODE_3RD_BYTE	  0x00
#define UART_CURRENT_OP_MODE				0x7018
#define UART_CURRENT_OP_MODE_H			0x70
#define UART_CURRENT_OP_MODE_L			0x18

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Driver status word
  *  Details of error information refer to object address[0x7011]
  *  Attribute = 16U,RO
  *     Unit   = [HEX]
  */

#define DRIVER_STATUS								0x604100
#define DRIVER_STATUS_1ST_BYTE			0x41
#define DRIVER_STATUS_2ND_BYTE			0x60
#define DRIVER_STATUS_3RD_BYTE			0x00
#define DRIVER_STATUS_NORMAL				0x0000U
#define DRIVER_STATUS_ERROR					0x0008U
#define UART_DRIVER_STATUS					0x7001
#define UART_DRIVER_STATUS_H				0x70
#define UART_DRIVER_STATUS_L			  0x01
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Emergency Stop
  *  Attribute = 08U,RW
  *     Unit   = [DEC]
  */

#define EMERGENCY_STOP							0x605A11
#define EMERGENCY_STOP_1ST_BYTE			0x5A
#define EMERGENCY_STOP_2ND_BYTE			0x60
#define EMERGENCY_STOP_3RD_BYTE			0x11
#define EMERGENCY_STOP_ENABLE				1
#define EMERGENCY_STOP_DISABLE			0
#define UART_EMERGENCY_STOP					0x701F
#define UART_EMERGENCY_STOP_H				0x70
#define UART_EMERGENCY_STOP_L				0x1F
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Acceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define ACCELERATION								0x608300
#define ACCELERATION_1ST_BYTE				0x83
#define ACCELERATION_2ND_BYTE				0x60
#define ACCELERATION_3RD_BYTE				0x00
#define UART_ACCELERATION						0x7099
#define UART_ACCELERATION_H					0x70
#define UART_ACCELERATION_L					0x99

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION								0x608400
#define DECELERATION_1ST_BYTE				0x84
#define DECELERATION_2ND_BYTE				0x60
#define DECELERATION_3RD_BYTE				0x00
#define UART_DECELERATION						0x709A
#define UART_DECELERATION_H					0x70
#define UART_DECELERATION_L					0x9A
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration in emergency stop
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION_IN_EMERGENCY						0x605A01
#define DECELERATION_IN_EMERGENCY_1					0x5A
#define DECELERATION_IN_EMERGENCY_2					0x60
#define DECELERATION_IN_EMERGENCY_3					0x01
#define UART_DECELERATION_IN_EMERGENCY			0x709B
#define UART_DECELERATION_IN_EMERGENCY_H		0x70
#define UART_DECELERATION_IN_EMERGENCY_L		0x9B
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target Velocity_rpm
  *  Valid in operation mode 3,-3
  *  Note:It will affect the value of object address [0x70B2]
  *  Attribute = 16S,RW
  *     Unit   = [rpm]
  */

#define DESIRE_VEL_RPM							0x2FF009
#define DESIRE_VEL_RPM_1ST_BYTE			0xF0
#define DESIRE_VEL_RPM_2ND_BYTE			0x2F
#define DESIRE_VEL_RPM_3RD_BYTE			0x09
#define UART_DESIRE_VEL_RPM					0x70B1
#define UART_DESIRE_VEL_RPM_H				0x70
#define UART_DESIRE_VEL_RPM_L				0xB1
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target Velocity_dec
  *  Valid in operation mode 3,-3
  *  U[y,x]:
  *   [DEC]=([rpm]*512*[Resolution])/1875;
  *   Resolution Default : 4096
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define DESIRE_VEL_DEC							0x60FF00
#define DESIRE_VEL_DEC_1ST_BYTE			0xFF
#define DESIRE_VEL_DEC_2ND_BYTE			0x60
#define DESIRE_VEL_DEC_3RD_BYTE			0x00
#define UART_DESIRE_VEL_DEC					0x70B2
#define UART_DESIRE_VEL_DEC_H				0x70
#define UART_DESIRE_VEL_DEC_L				0xB2
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Max following error
  *  Only valid in mode 1 when Kpp0 is not 0
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define MAX_FOLLOWING_ERR						0x606500
#define MAX_FOLLOWING_ERR_1ST_BYTE	0x65
#define MAX_FOLLOWING_ERR_2ND_BYTE	0x60
#define MAX_FOLLOWING_ERR_3RD_BYTE	0x00
#define UART_MAX_FOLLOWING_ERR			0x7093
#define UART_MAX_FOLLOWING_ERR_H		0x70
#define UART_MAX_FOLLOWING_ERR_L		0x93
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Position loop speed feedforward
  *  valid in mode 1
  *  Range:0~256,corresponding to 0~100%
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define POS_LOOP_SPEED_FF						0x60FB02
#define POS_LOOP_SPEED_FF_1ST_BYTE	0xFB
#define POS_LOOP_SPEED_FF_2ND_BYTE	0x60
#define POS_LOOP_SPEED_FF_3RD_BYTE	0x02
#define UART_POS_LOOP_SPEED_FF			0x709C
#define UART_POS_LOOP_SPEED_FF_H		0x70
#define UART_POS_LOOP_SPEED_FF_L		0x9C
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kpp0, propotion gain 0 in position loop
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_POSITION					0x60FB01
#define PROPOTION_GAIN_IN_POS_1							0xFB
#define PROPOTION_GAIN_IN_POS_2							0x60
#define PROPOTION_GAIN_IN_POS_3							0x01
#define UART_PROPOTION_GAIN_IN_POSITION 		0x7094
#define UART_PROPOTION_GAIN_IN_POSITION_H 	0x70
#define UART_PROPOTION_GAIN_IN_POSITION_L 	0x94
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvp0,propotion gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_SPEED					0x60F901
#define PROPOTION_GAIN_IN_SPEED_1				0xF9
#define PROPOTION_GAIN_IN_SPEED_2				0x60
#define PROPOTION_GAIN_IN_SPEED_3				0x01
#define UART_PROPOTION_GAIN_IN_SPEED		0x70B3
#define UART_PROPOTION_GAIN_IN_SPEED_H	0x70
#define UART_PROPOTION_GAIN_IN_SPEED_L	0xB3
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvi0,integrator gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define INTEGRATOR_GAIN_IN_SPEED					0x60F902
#define INTEGRATOR_GAIN_IN_SPEED_1				0xF9
#define INTEGRATOR_GAIN_IN_SPEED_2				0x60
#define INTEGRATOR_GAIN_IN_SPEED_3				0x02
#define UART_INTEGRATOR_GAIN_IN_SPEED			0x70B4
#define UART_INTEGRATOR_GAIN_IN_SPEED_H		0x70
#define UART_INTEGRATOR_GAIN_IN_SPEED_L		0xB4
/* SPEED MODE END */
#endif

#ifdef BASIC_MODE_ON
/* BASIC MODE START */
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Operation mode
  *  Attribute = 08S,RW,S5
  *     Unit   = [DEC]
  *  Operation mode
  * 	-3 Speed mode without Acc/Dec
  * 	1 Position mode
  * 	3 Speed mode with Acc/Dec
  *		4 Torque mode
  */

#define OPERATION_MODE							0x606000
#define OPERATION_MODE_1ST_BYTE			0x60
#define OPERATION_MODE_2ND_BYTE			0x60
#define OPERATION_MODE_3RD_BYTE			0x00
#define SPEED_MODE_WITH_ACCEL_DECEL	3
#define SPEED_MODE									-3
#define TORQUE_MODE									4
#define POSITION_MODE								1

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Control Word
  *  Attribute = 16S,RW
  *     Unit   = [HEX]
  */

#define CONTROL_WORD								0x604000
#define CONTROL_WORD_1ST_BYTE				0x40
#define CONTROL_WORD_2ND_BYTE				0x60
#define CONTROL_WORD_3RD_BYTE				0x00
#define CONTROL_WORD_ENABLE					(int16_t)0x0F
#define CONTROL_WORD_DISABLE				(int16_t)0x06
#define CONTROL_WORKD_CLEAR					(int16_t)0x86

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Current Operation mode
  *  Attribute = 08S,RO
  *     Unit   = [DEC]
  */

#define CURRENT_OP_MODE							0x606100
#define CURRENT_OP_MODE_1ST_BYTE		0x61
#define CURRENT_OP_MODE_2ND_BYTE		0x60
#define CURRENT_OP_MODE_3RD_BYTE	  0x00


/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Driver status word
  *  Details of error information refer to object address[0x7011]
  *  Attribute = 16U,RO
  *     Unit   = [HEX]
  */

#define DRIVER_STATUS								0x604100
#define DRIVER_STATUS_1ST_BYTE			0x41
#define DRIVER_STATUS_2ND_BYTE			0x60
#define DRIVER_STATUS_3RD_BYTE			0x00
#define DRIVER_STATUS_NORMAL				0x0000U
#define DRIVER_STATUS_ERROR					0x0008U
#define DRIVER_STATUS_ERROR_1ST_B		0x08U

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Driver error code 1
  * Each bit indicates one error as shown in follows:
  * Attribute = 16U,RO
  *    Unit   = [HEX]
  */
	
#define DRIVER_ERROR 								0x260100
#define DRIVER_ERROR_1ST_BYTE 			0x01
#define DRIVER_ERROR_2ND_BYTE 			0x26
#define DRIVER_ERROR_3RD_BYTE 			0x00
//#define DRIVER_ERROR_INTERNAL_ERROR //TO CHECK PDF FOR BIT REGISTER ASSIGN
#define UART_DRIVER_ERROR						0x7011
#define UART_DRIVER_ERROR_H					0x70
#define UART_DRIVER_ERROR_L					0x11
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Emergency Stop
  *  Attribute = 08U,RW
  *     Unit   = [DEC]
  */

#define EMERGENCY_STOP							0x605A11
#define EMERGENCY_STOP_1ST_BYTE			0x5A
#define EMERGENCY_STOP_2ND_BYTE			0x60
#define EMERGENCY_STOP_3RD_BYTE			0x11
#define EMERGENCY_STOP_ENABLE				1
#define EMERGENCY_STOP_DISABLE			0

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target position in absolute positioning ( Valid in operation mode 1 )
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define ABSOLUTE_TARGET_POSITION					0x607A00
#define ABSOLUTE_TARGET_POSITION_1				0x7A
#define ABSOLUTE_TARGET_POSITION_2				0x60
#define ABSOLUTE_TARGET_POSITION_3				0x00
#define UART_ABSOLUTE_TARGET_POSITION			0x7091
#define UART_ABSOLUTE_TARGET_POSITION_H		0x70
#define UART_ABSOLUTE_TARGET_POSITION_L		0x91
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target position in relative positioning ( Valid in operation mode 1 )
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define RELATIVE_TARGET_POSITION					0x607B00
#define RELATIVE_TARGET_POSITION_1				0x7B
#define RELATIVE_TARGET_POSITION_2				0x60
#define RELATIVE_TARGET_POSITION_3				0x00
#define UART_RELATIVE_TARGET_POSITION			0x709F
#define UART_RELATIVE_TARGET_POSITION_H		0x70
#define UART_RELATIVE_TARGET_POSITION_L		0x9F
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Profile velocity_dec ( valid in operation mode 1 )
	* U[y,x]:
  *	[DEC]=([rpm]*512*[Resolution])/1875; [Resolution]Default:4096
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define VELOCITY_DEC  				 			0x608100
#define VELOCITY_DEC_1ST_BYTE  			0x81
#define VELOCITY_DEC_2ND_BYTE  			0x60
#define VELOCITY_DEC_3RD_BYTE  			0x00
#define UART_VELOCITY_DEC 					0x7098
#define UART_VELOCITY_DEC_H 				0x70
#define UART_VELOCITY_DEC_L 				0x98
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Profile velocity_rpm ( Target speed in operation mode 1 )
  * Note -> This object will affect the value of object [ 0x7098 ]
  *  Attribute = 16U,RW, S5
  *     Unit   = [rpm]
  */

#define VELOCITY_RPM								0x608200
#define VELOCITY_RPM_1ST_BYTE				0x82
#define VELOCITY_RPM_2ND_BYTE				0x60
#define VELOCITY_RPM_3RD_BYTE				0x00
#define UART_VELOCITY_RPM						0x709D
#define UART_VELOCITY_RPM_H					0x70
#define UART_VELOCITY_RPM_L					0x9D
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Acceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * 5
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define ACCELERATION								0x608300
#define ACCELERATION_1ST_BYTE				0x83
#define ACCELERATION_2ND_BYTE				0x60
#define ACCELERATION_3RD_BYTE				0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * 5
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION								0x608400
#define DECELERATION_1ST_BYTE				0x84
#define DECELERATION_2ND_BYTE				0x60
#define DECELERATION_3RD_BYTE				0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Deceleration in emergency stop
  * U[y,x]:
  * [DEC] = [rps/s]*256*[Resolution]/1562
  * Resolution = 4096 [ default ]
  *  Attribute = 32U,RW, S5
  *     Unit   = [DEC]
  */

#define DECELERATION_IN_EMERGENCY		0x605A01
#define DECELERATION_IN_EMERGENCY_1	0x5A
#define DECELERATION_IN_EMERGENCY_2	0x60
#define DECELERATION_IN_EMERGENCY_3	0x01

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target Velocity_rpm
  *  Valid in operation mode 3,-3
  *  Note:It will affect the value of object address [0x70B2]
  *  Attribute = 16S,RW
  *     Unit   = [rpm]
  */

#define DESIRE_VEL_RPM							0x2FF009
#define DESIRE_VEL_RPM_1ST_BYTE			0xF0
#define DESIRE_VEL_RPM_2ND_BYTE			0x2F
#define DESIRE_VEL_RPM_3RD_BYTE			0x09

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Target Velocity_dec
  *  Valid in operation mode 3,-3
  *  U[y,x]:
  *   [DEC]=([rpm]*512*[Resolution])/1875;
  *   Resolution Default : 4096
  *  Attribute = 32S,RW
  *     Unit   = [DEC]
  */

#define DESIRE_VEL_DEC							0x60FF00
#define DESIRE_VEL_DEC_1ST_BYTE			0xFF
#define DESIRE_VEL_DEC_2ND_BYTE			0x60
#define DESIRE_VEL_DEC_3RD_BYTE			0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Output current
  *  （Setting output current for operation mode 4）
  *  U[y,x]:
  *   [DEC]=[Arms]*1.414*2048/Driver max. output current
	*		L2DB4830 max. output current is 33Ap
  *  Attribute = 16S,RW
  *     Unit   = [DEC]
  */

#define OUTPUT_CURRENT    				  0x60F608
#define OUTPUT_CURRENT_1ST_BYTE     0xF6
#define OUTPUT_CURRENT_2ND_BYTE     0x60
#define OUTPUT_CURRENT_3RD_BYTE	    0x08
#define UART_OUTPUT_CURRENT					0x70E1
#define UART_OUTPUT_CURRENT_H				0x70
#define UART_OUTPUT_CURRENT_L				0xE1
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Output current limit
  * Valid in all operation mode
  *  U[y,x]:
  *   [DEC]=[Arms]*1.414*2048/Driver max. output current
	*		L2DB4830 max. output current is 33Ap
  *  Attribute = 16U,RW
  *     Unit   = [DEC]
  */

#define OUTPUT_CURRENT_LIMIT        0x607300
#define OUTPUT_CURRENT_LIMIT_1    	0x73
#define OUTPUT_CURRENT_LIMIT_2   		0x60
#define OUTPUT_CURRENT_LIMIT_3    	0x00
#define UART_OUTPUT_CURRENT_LIMIT		0x70E2
#define UART_OUTPUT_CURRENT_LIMIT_H	0x70
#define UART_OUTPUT_CURRENT_LIMIT_L	0xE2
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Max. speed_rpm
  * Setting maximum speed in all operation mode
  *  Attribute = 16U,RW,S5
  *     Unit   = [DEC]
  */
	
#define MAX_SPEED_RPM              	0x608000
#define MAX_SPEED_RPM_1ST_BYTE     	0x80
#define MAX_SPEED_RPM_2ND_BYTE     	0x60
#define MAX_SPEED_RPM_3RD_BYTE     	0x00
#define UART_MAX_SPEED_RPM 					0x70B8
#define UART_MAX_SPEED_RPM_H 				0x70
#define UART_MAX_SPEED_RPM_L 				0xB8
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Max. position following error
  * Valid in operation mode 1 when "Kpp" is not 0
  *  Attribute = 32U,RW,S5
  *     Unit   = [DEC]
  */
	
#define MAX_POS_FOLLOWING_ERROR     0x606500
#define MAX_POS_FOLLOWING_ERR0R_1   0x65
#define MAX_POS_FOLLOWING_ERROR_2   0x60
#define MAX_POS_FOLLOWING_ERROR_3   0x00

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Position compensation for operation mode 3:
  *  Attribute = 08U,RW,S5
  *     Unit   = [DEC]
  */
	
#define POS_COMPENSATION            0x60FB88
#define POS_COMPENSATION_1ST_BYTE   0xFB
#define POS_COMPENSATION_2ND_BYTE   0x60
#define POS_COMPENSATION_3RD_BYTE   0x88
#define POS_COMPENSATION_DISABLE    0
#define POS_COMPENSATION_ENABLE			1
#define UART_POS_COMPENSATION 			0x8088
#define UART_POS_COMPENSATION_H 		0x80
#define UART_POS_COMPENSATION_L 		0x88
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Position loop speed feedforward
  *  valid in mode 1
  *  Range:0~256,corresponding to 0~100%
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define POS_LOOP_SPEED_FF						0x60FB02
#define POS_LOOP_SPEED_FF_1ST_BYTE	0xFB
#define POS_LOOP_SPEED_FF_2ND_BYTE	0x60
#define POS_LOOP_SPEED_FF_3RD_BYTE	0x02

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kpp0, propotion gain 0 in position loop
  *  Attribute = 16S,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_POSITION	0x60FB01
#define PROPOTION_GAIN_IN_POS_1			0xFB
#define PROPOTION_GAIN_IN_POS_2			0x60
#define PROPOTION_GAIN_IN_POS_3			0x01

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvp0,propotion gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define PROPOTION_GAIN_IN_SPEED			0x60F901
#define PROPOTION_GAIN_IN_SPEED_1		0xF9
#define PROPOTION_GAIN_IN_SPEED_2		0x60
#define PROPOTION_GAIN_IN_SPEED_3		0x01

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Kvi0,integrator gain 0 in speed loop
  *  Attribute = 16U,RW, S5
  *     Unit   = [DEC]
  */

#define INTEGRATOR_GAIN_IN_SPEED		0x60F902
#define INTEGRATOR_GAIN_IN_SPEED_1	0xF9
#define INTEGRATOR_GAIN_IN_SPEED_2	0x60
#define INTEGRATOR_GAIN_IN_SPEED_3	0x02

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Clear actual position
	* Set 1 to clear "Actual position" when motor is disable
  *  Attribute = 08U,RW
  *     Unit   = [DEC]
  */

#define CLEAR_ACTUAL_POSITION          0x607C02
#define CLEAR_ACTUAL_POSITION_1Byte    0x7C
#define CLEAR_ACTUAL_POSITION_2Byte    0x60
#define CLEAR_ACTUAL_POSITION_3Byte    0x02
#define UART_CLEAR_ACTUAL_POSITION		 0x70AC
#define UART_CLEAR_ACTUAL_POSITION_H	 0x70
#define UART_CLEAR_ACTUAL_POSITION_L	 0xAC
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Noise reduction at zero speed
  *  Attribute = 08U,RW,S5
  *     Unit   = [DEC]
  */
	
#define NOISE_REDUCTION          				0x500050
#define NOISE_REDUCTION_1Byte        		0x00
#define NOISE_REDUCTION_2Byte        		0x50
#define NOISE_REDUCTION_3Byte        		0x50
#define NOISE_REDUCTION_DISABLE  				0   //DEFALUT
#define NOISE_REDUCTION_ENABLE   				1
#define UART_NOISE_REDUCTION						0x701C
#define UART_NOISE_REDUCTION_H					0x70
#define UART_NOISE_REDUCTION_L					0x1C
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Noise reduction delay time for enable
	* Defalut:500
  *  Attribute = 16U,RW,S5
  *     Unit   = [mS]
  */
	
#define NOISE_REDUCT_DELAY_TIME     		0x500051
#define NOISE_REDUCT_DELAY_TIME_1   		0x00
#define NOISE_REDUCT_DELAY_TIME_2   		0x50
#define NOISE_REDUCT_DELAY_TIME_3   		0x51
#define UART_NOISE_REDUCT_DELAY_TIME 		0x701D
#define UART_NOISE_REDUCT_DELAY_TIME_H 	0x70
#define UART_NOISE_REDUCT_DELAY_TIME_L 	0x1D
/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Max. temperature for driver over-temperature protection
  *  Attribute = 16U,RW,S3
  *     Unit   = ['C]
  */
	
#define MAX_TEMPERATURE_DRIVER      		0x300015
#define MAX_TEMPERATURE_DRIVER_1    		0x00
#define MAX_TEMPERATURE_DRIVER_2    		0x30
#define MAX_TEMPERATURE_DRIVER_3    		0x15
#define UART_MAX_TEMPERATURE_DRIVER 		0x7004
#define UART_MAX_TEMPERATURE_DRIVER_H 	0x70
#define UART_MAX_TEMPERATURE_DRIVER_L 	0x04
/* BASIC MODE END */
#endif


/* MOTOR PARAMTER START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Current motor code
 * Attribute = 16U,RO
 *  Unit = [HEX]
 */

#define CURRENT_MOTOR_CODE      		0x641016
#define CURRENT_MOTOR_CODE_1 				0x10
#define CURRENT_MOTOR_CODE_2				0x64
#define CURRENT_MOTOR_CODE_3    		0x16
#define UART_CURRENT_MOTOR_CODE			0x7046
#define UART_CURRENT_MOTOR_CODE_H		0x70
#define UART_CURRENT_MOTOR_CODE_L		0x46
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor code setting
 * Attribute = 16U,RW,S4
 *   Unit = [HEX]
 */

#define MOTOR_CODE_SETTING     	  	0x641001
#define MOTOR_CODE_SETTING_1      	0x10
#define MOTOR_CODE_SETTING_2      	0x64
#define MOTOR_CODE_SETTING_3      	0x01
#define UART_MOTOR_CODE_SETTING			0x7031
#define UART_MOTOR_CODE_SETTING_H		0x70
#define UART_MOTOR_CODE_SETTING_L		0x31
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Feedback type
 * Attribute = 08U,RW,S4
 *   Unit = [HEX]
 */

#define FEEDBACK_TYPE								0x641002
#define FEEDBACK_TYPE_1							0x10
#define FEEDBACK_TYPE_2							0x64
#define FEEDBACK_TYPE_3							0x02
#define UART_FEEDBACK_TYPE					0x7032
#define UART_FEEDBACK_TYPE_H				0x70
#define UART_FEEDBACK_TYPE_L				0x32
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Encoder resolution
 * Defalut:4096
 * Attribute = 32U,RW,S4
 *   Unit = [DEC]
 */

#define ENCODER_RESOLUTION					0x641003
#define ENCODER_RESOLUTION_1				0x10
#define ENCODER_RESOLUTION_2				0x64
#define ENCODER_RESOLUTION_3				0x03	
#define UART_ENCODER_RESOLUTION			0x7033
#define UART_ENCODER_RESOLUTION_H		0x70
#define UART_ENCODER_RESOLUTION_L		0x33
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor pole pair
 * Attribute = 08U,RW,S4
 *   Unit = [DEC]
 */

#define MOTOR_POLE_PAIR							0x641005
#define MOTOR_POLE_PAIR_1						0x10
#define MOTOR_POLE_PAIR_2						0x64
#define MOTOR_POLE_PAIR_3						0x05
#define UART_MOTOR_POLE_PAIR				0x7035
#define UART_MOTOR_POLE_PAIR_H			0x70
#define UART_MOTOR_POLE_PAIR_L			0x35
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Exciting mode
 * Attribute = 08U,RW,S4
 *   Unit = [DEC]
 */

#define EXCITING_MODE								0x641006
#define EXCITING_MODE_1							0x10
#define EXCITING_MODE_2							0x64
#define EXCITING_MODE_3							0x06
#define UART_EXCITING_MODE					0x7036
#define UART_EXCITING_MODE_H				0x70
#define UART_EXCITING_MODE_L				0x36
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Exciting current
 * Attribute = 16S,RW,S4
 *   Unit = [DEC]
 */

#define EXCITING_CURRENT						0x641007
#define EXCITING_CURRENT_1					0x10
#define EXCITING_CURRENT_2					0x64
#define EXCITING_CURRENT_3					0x07
#define UART_EXCITING_CURRENT				0x7037
#define UART_EXCITING_CURRENT_H			0x70
#define UART_EXCITING_CURRENT_L			0x37
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Exciting time
 * Attribute = 16U,RW,S4
 *   Unit = [ms]
 */

#define EXCITING_TIME								0x641008
#define EXCITING_TIME_1							0x10
#define EXCITING_TIME_2							0x64
#define EXCITING_TIME_3							0x08
#define UART_EXCITING_TIME					0x7038
#define UART_EXCITING_TIME_H				0x70
#define UART_EXCITING_TIME_L				0x38	
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor IIt current 
 * Attribute = 16U,RW,S4
 *   Unit = [0.1A]
 */
 
#define MOTOR_IIT_CURRENT						0x641009
#define MOTOR_IIT_CURRENT_1					0x10
#define MOTOR_IIT_CURRENT_2					0x64
#define MOTOR_IIT_CURRENT_3					0x09
#define UART_MOTOR_IIT_CURRENT			0x7039
#define UART_MOTOR_IIT_CURRENT_H		0x70
#define UART_MOTOR_IIT_CURRENT_L		0x39
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor IIt time
 * Attribute = 16U,RW,S4
 *   Unit = [S]
 */

#define MOTOR_IIT_TIME							0x64100A
#define MOTOR_IIT_TIME_1						0x10
#define MOTOR_IIT_TIME_2						0x64
#define MOTOR_IIT_TIME_3						0x0A
#define UART_MOTOR_IIT_TIME					0x703A
#define UART_MOTOR_IIT_TIME_H				0x70
#define UART_MOTOR_IIT_TIME_L				0x3A
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor max. current
 * Attribute = 16U,RW,S4
 *   Unit = [0.1A]
 */

#define MOTOR_MAX_CURRENT						0x64100B
#define MOTOR_MAX_CURRENT_1					0x10
#define MOTOR_MAX_CURRENT_2					0x64
#define MOTOR_MAX_CURRENT_3					0x0B
#define UART_MOTOR_MAX_CURRENT			0x703B
#define UART_MOTOR_MAX_CURRENT_H		0x70
#define UART_MOTOR_MAX_CURRENT_L		0x3B
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor rotation direction
 * Attribute = 08U,RW,S4
 *   Unit = [DEC]
 */

#define MOTOR_ROTATION_DIR					0x641013
#define MOTOR_ROTATION_DIR_1				0x10
#define MOTOR_ROTATION_DIR_2				0x64
#define MOTOR_ROTATION_DIR_3				0x13
#define UART_MOTOR_ROTATION_DIR			0x7043
#define UART_MOTOR_ROTATION_DIR_H		0x70
#define UART_MOTOR_ROTATION_DIR_L		0x43
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor rated speed 
 * Attribute = 16U,RW,S4
 *   Unit = [rpm]
 */
 
#define MOTOR_RATED_SPEED						0x64101A
#define MOTOR_RATED_SPEED_1					0x10
#define MOTOR_RATED_SPEED_2					0x64
#define MOTOR_RATED_SPEED_3					0x1A
#define UART_MOTOR_RATED_SPEED			0x704A
#define UART_MOTOR_RATED_SPEED_H		0x70
#define UART_MOTOR_RATED_SPEED_L		0x4A
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor rated power 
 * Attribute = 16U,RW,S4
 *   Unit = [W]
 */
 
#define MOTOR_RATED_PW							0x64101B
#define MOTOR_RATED_PW_1						0x10
#define MOTOR_RATED_PW_2						0x64
#define MOTOR_RATED_PW_3						0x1B
#define UART_MOTOR_RATED_PW					0x704B
#define UART_MOTOR_RATED_PW_H				0x70
#define UART_MOTOR_RATED_PW_L				0x4B
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor hall angle
 * Attribute = 16U,RW,S4
 *   Unit = [Degree]
 */
 
#define MOTOR_HALL_ANGLE						0x64101F
#define MOTOR_HALL_ANGLE_1					0x10
#define MOTOR_HALL_ANGLE_2					0x64
#define MOTOR_HALL_ANGLE_3					0x1F
#define UART_MOTOR_HALL_ANGLE				0x704F
#define UART_MOTOR_HALL_ANGLE_H			0x70
#define UART_MOTOR_HALL_ANGLE_L			0x4F
/* MOTOR PARAMTER END */

/* MEASRUEMENT DATA START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual position
 * Attribute = 32s,RO
 *   Unit = [DEC]
 */

#define ACTUAL_POSITION							0x606300
#define ACTUAL_POSITION_1						0x63
#define ACTUAL_POSITION_2						0x60
#define ACTUAL_POSITION_3						0x00
#define UART_ACTUAL_POSITION				0x7071
#define UART_ACTUAL_POSITION_H			0x70
#define UART_ACTUAL_POSITION_L			0x71
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual speed_rpm
 * Sampling cycle can be changed i object 0x7079
 * Resolution: 1rpm
 * Attribute = 16s,RO
 *   Unit = [1rpm]
 */
 
#define ACTUAL_SPEED_RPM						0x60F918
#define ACTUAL_SPEED_RPM_1Byte			0xF9
#define ACTUAL_SPEED_RPM_2Byte			0x60
#define ACTUAL_SPEED_RPM_3Byte			0x18	
#define UART_ACTUAL_SPEED_RPM				0x7075
#define UART_ACTUAL_SPEED_RPM_H			0x70
#define UART_ACTUAL_SPEED_RPM_L			0x75
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual speed_0.001rpm
 * Sampling cycle can be changed i object 0x7079
 * Resolution: 0.001rpm
 * Attribute = 32s,RO
 *   Unit = [0.001rpm]
 */
 
#define ACTUAL_SPEED_0001_RPM						0x60F919
#define ACTUAL_SPEED_0001_RPM_1					0xF9
#define ACTUAL_SPEED_0001_RPM_2					0x60
#define ACTUAL_SPEED_0001_RPM_3					0x19
#define UART_ACTUAL_SPEED_0001_RPM			0x7076
#define UART_ACTUAL_SPEED_0001_RPM_H		0x70
#define UART_ACTUAL_SPEED_0001_RPM_L		0x76
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Sampling cycle for actual speed
 * Default:30
 * Attribute = 16U,RW,S5
 *   Unit = [ms]
 */
 
#define SAMPLE_CYCLE_ACTUAL_SPEED						0x60F91A
#define SAMPLE_CYCLE_ACTUAL_SPEED_1Byte			0xF9
#define SAMPLE_CYCLE_ACTUAL_SPEED_2Byte			0x60
#define SAMPLE_CYCLE_ACTUAL_SPEED_3Byte			0x1A
#define UART_SAMPLE_CYCLE_ACTUAL_SPEED			0x7079
#define UART_SAMPLE_CYCLE_ACTUAL_SPEED_H		0x70
#define UART_SAMPLE_CYCLE_ACTUAL_SPEED_L		0x79
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual speed_DEC
 * Sampling cycle is 250uS
 *[DEC]=([rpm]*512*[Resolution])/1875; [Resolution]Default:4096
 * Note:the value vibration is big because sampling cycle is too short.
 * Attribute = 32s,RO
 *   Unit = [DEC]
 */
 
#define ACTUAL_SPEED_DEC						0x606C00
#define ACTUAL_SPEED_DEC_1					0x6C
#define ACTUAL_SPEED_DEC_2					0x60
#define ACTUAL_SPEED_DEC_3					0x00	
#define UART_ACTUAL_SPEED_DEC				0x7077
#define UART_ACTUAL_SPEED_DEC_H			0x70
#define UART_ACTUAL_SPEED_DEC_L			0x77
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual current_Iq
 * [DEC]=[Arms]*1.414*2048/I_MAX
 * Note:For L2DB4830 series，I_MAX=33；
 * Attribute = 16S,RO
 *   Unit = [DEC]
 */
 
#define ACTUAL_CURRENT_Iq						0x607800
#define ACTUAL_CURRENT_Iq_1					0x78
#define ACTUAL_CURRENT_Iq_2					0x60
#define ACTUAL_CURRENT_Iq_3					0x00
#define UART_ACTUAL_CURRENT_Iq			0x7072
#define UART_ACTUAL_CURRENT_Iq_H		0x70
#define UART_ACTUAL_CURRENT_Iq_L		0x72
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Motor actual IIt current
 * Attribute = 16U,RO
 *   Unit = [mA]
 */
 
#define MOTOR_ACUTAL_IIt_CURRENT					0x60F632
#define MOTOR_ACUTAL_IIt_CURRENT_1				0xF6
#define MOTOR_ACUTAL_IIt_CURRENT_2				0x60
#define MOTOR_ACUTAL_IIt_CURRENT_3				0x32
#define UART_MOTOR_ACUTAL_IIt_CURRENT			0x7007
#define UART_MOTOR_ACUTAL_IIt_CURRENT_H		0x70
#define UART_MOTOR_ACUTAL_IIt_CURRENT_L		0x07
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual DC bus voltage
 * Resolution:1V
 * Attribute = 16S,RO
 *   Unit = [V]
 */
 
#define ACTUAL_DC_VOLTAGE						0x60F712
#define ACTUAL_DC_VOLTAGE_1					0xF7
#define ACTUAL_DC_VOLTAGE_2					0x60
#define ACTUAL_DC_VOLTAGE_3					0x12
#define UART_ACTUAL_DC_VOLTAGE			0x5001
#define UART_ACTUAL_DC_VOLTAGE_H		0x50
#define UART_ACTUAL_DC_VOLTAGE_L		0x01
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Driver actual temperature
 * Attribute = 16S,RO
 *   Unit = ['C]
 */
 
#define DRIVER_ACTUAL_TEMP					0x60F70B
#define DRIVER_ACTUAL_TEMP_1				0xF7
#define DRIVER_ACTUAL_TEMP_2				0x60
#define DRIVER_ACTUAL_TEMP_3				0x0B
#define UART_DRIVER_ACTUAL_TEMP			0x7002
#define UART_DRIVER_ACTUAL_TEMP_H		0x70
#define UART_DRIVER_ACTUAL_TEMP_L		0x02
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual position following error
 * Attribute = 32S,RO
 *   Unit = [DEC]
 */
 
#define ACTUAL_POSITION_ERROR					0x60F400
#define ACTUAL_POSITION_ERROR_1				0xF4
#define ACTUAL_POSITION_ERROR_2				0x60
#define ACTUAL_POSITION_ERROR_3				0x00
#define UART_ACTUAL_POSITION_ERROR		0x7092
#define UART_ACTUAL_POSITION_ERROR_H	0x70
#define UART_ACTUAL_POSITION_ERROR_L	0x92
/* MEASRUEMENT DATA END */

/* IO PORT SETTING START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Actual states of digital input(Hardware states) 
 * BIT[0]—DIN1_State
 * BIT[1]—DIN2_State
 *  …
 * BIT[7]—DIN8_State
 * The corresponding bit will be set 1 when DINx is valid,or it will be set 0 
 * Attribute = 16U,RO
 *    Unit = [BIT]
 */

#define ACTUAL_STATE_DIGI_INPUT			0x20100A
#define ACTUAL_STATE_DIGI_INPUT_1		0x10
#define ACTUAL_STATE_DIGI_INPUT_2		0x20
#define ACTUAL_STATE_DIGI_INPUT_3		0x0A

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Digital input polarity setting
 * BIT[0]—DIN1_Polarity
 * BIT[1]—DIN2_Polarity 
 * …
 * BIT[7]—DIN8_Polarity
 * DIN[x+1] polarity is negation when BIT[x] is set as 0
 * Default：0x00ff
 * Attributes = 16U,RO,S2
 *   Unit = [BIT]
 */
 
#define DIGI_INPUT_POLARITY_SET			0x201001
#define DIGI_INPUT_POLARITY_SET_1		0x10
#define DIGI_INPUT_POLARITY_SET_2		0x20
#define DIGI_INPUT_POLARITY_SET_3		0x01

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Digital input simulate
 * BIT[0]—DIN1_Simulate
 * BIT[1]—DIN2_Simulate
 * …
 * BIT[7]—DIN8_Simulate
 * DIN[x+1] is valid when BIT[x] as 1
 * Attributes = 16U,RW
 *   Unit = [BIT]
 */
 
#define DIGI_INPUT_SIMULATE					0x201002
#define DIGI_INPUT_SIMULATE_1				0x10
#define DIGI_INPUT_SIMULATE_2				0x20
#define DIGI_INPUT_SIMULATE_3				0x02

/* IO PORT SETTING END */

/* COMMUNICATION PARAMETERS START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * UART baudrate setting
 * Setting value    baudrate
 * 		    3          19200
 *	    	4          38400
 * 	     	5          56000
 * 	     	6          57600
 * 		    7         115200
 * It must save and reboot driver. 
 * Default:7
 * Attribute = 08U,RW,S1
 *    Unit = [DEC]
 */
 
#define UART_BAUNDRATE_SET					0x2FE001
#define UART_BAUNDRATE_SET_1				0xE0
#define UART_BAUNDRATE_SET_2				0x2F
#define UART_BAUNDRATE_SET_3				0x01

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * RS485/CAN ID
 * Activate when DIP switch SW3 set as OFF 
 * Default:17
 * Attribute = 08U,RW,S1 
 *   Unit = [DEC]
 */
 
#define RS485_CAN_ID								0x65100F
#define RS485_CAN_ID_1							0x10
#define RS485_CAN_ID_2							0x65
#define RS485_CAN_ID_3							0x0F

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Communication loss protection
 * 0:Disable
 * 1:Enable
 * Default:depend on different model
 * Attribute = 08U,RW,S1
 *    Unit = [DEC]
 */
 
#define COMMUNICATION_LOSS_PROTECT					0x410010 
#define COMMUNICATION_LOSS_PROTECT_1				0x00 
#define COMMUNICATION_LOSS_PROTECT_2				0x41 
#define COMMUNICATION_LOSS_PROTECT_3				0x10 
#define COMMUNICATION_LOSS_PROTECT_DISABLE	0
#define COMMUNICATION_LOSS_PROTECT_ENABLE		1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Communication loss delay time
 * Default:600
 * Attribute = 32U,RW,S1
 *   Unit = [mS]
 */
 
#define COMMUNICATION_LOSS_DELAY		0x410011
#define COMMUNICATION_LOSS_DELAY_1	0x00
#define COMMUNICATION_LOSS_DELAY_2	0x41
#define COMMUNICATION_LOSS_DELAY_3	0x11

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Simple PDO function
 * 0：Disable
 * 1：Enable TXPDO1（Auto-upload "Actual position" and "Actual velocity_0.001rpm" ）
 * Default：0
 * Attribute = 08U,RW
 *    Unit = [DEC]
 */
 
#define SIMPLE_PDO_FUN							0x470001
#define SIMPLE_PDO_FUN_1						0x00
#define SIMPLE_PDO_FUN_2						0x47
#define SIMPLE_PDO_FUN_3						0x01
#define SIMPLE_PDO_FUN_DISABLE			0
#define SIMPLE_PDO_FUN_ENABLE				1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * TX-PDO1 prohibit time
 * Default:10ms
 * Attribute = 16U,RW
 *    Unit = [mS]
 */
 
#define TX_PDO1_PROHIBIT_TIME				0x180003
#define TX_PDO1_PROHIBIT_TIME_1			0x00
#define TX_PDO1_PROHIBIT_TIME_2			0x18
#define TX_PDO1_PROHIBIT_TIME_3			0x03 

/* Communication Parameters End */

/* PARAMETERS STORAGE START */

 /**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Save group S1 parameters
 * 1:Save
 * Attribute = 08U,RW
 *   Unit = [DEC]
 */
 
#define SAVE_GROUP_S1								0x2FE501
#define SAVE_GROUP_S1_1							0xE5
#define SAVE_GROUP_S1_2 						0x2F
#define SAVE_GROUP_S1_3							0x01
#define SAVE_GROUP_S1_SAVE					1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Save group S2 parameters
 * 1:Save
 * Attribute = 08U,RW
 *   Unit = [DEC]
 */
 
#define SAVE_GROUP_S2								0x2FE502
#define SAVE_GROUP_S2_1							0xE5
#define SAVE_GROUP_S2_2 						0x2F
#define SAVE_GROUP_S2_3							0x02
#define SAVE_GROUP_S2_SAVE					1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Save group S3 parameters
 * 1:Save
 * Attribute = 08U,RW
 *   Unit = [DEC]
 */
 
#define SAVE_GROUP_S3								0x2FE503
#define SAVE_GROUP_S3_1							0xE5
#define SAVE_GROUP_S3_2 						0x2F
#define SAVE_GROUP_S3_3							0x03
#define SAVE_GROUP_S3_SAVE					1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Save group S4 parameters
 * 1:Save
 * Attribute = 08U,RW
 *   Unit = [DEC]
 */
 
#define SAVE_GROUP_S4								0x2FE504
#define SAVE_GROUP_S4_1							0xE5
#define SAVE_GROUP_S4_2							0x2F
#define SAVE_GROUP_S4_3							0x04
#define SAVE_GROUP_S4_SAVE					1

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Save group S5 parameters
 * 1:Save
 * Attribute = 08U,RW
 *   Unit = [DEC]
 */
 
#define SAVE_GROUP_S5								0x2FE505
#define SAVE_GROUP_S5_1							0xE5
#define SAVE_GROUP_S5_2 						0x2F
#define SAVE_GROUP_S5_3							0x05
#define SAVE_GROUP_S5_SAVE					1

/* PARAMETERS STORAGE END */

/* DRIVER ATTRIBUTE START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Driver mode 1 - series
 * Default:L2DB
 * Attribute = 32U,RO
 *   Unit = [ASCII]
 */
 
#define DRIVER_MODE_1_SERIES				0x30003A
#define DRIVER_MODE_1_SERIES_1			0x00
#define DRIVER_MODE_1_SERIES_2			0x30
#define DRIVER_MODE_1_SERIES_3			0x3A

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Driver mode 2 – voltage and current
 * Default:4830
 * Attribute = 32U,RO
 *   Unit = [ASCII]
 */
 
#define DRIVER_MODE_2_VOLT_CURR			0x30003B
#define DRIVER_MODE_2_VOLT_CURR_1		0x00
#define DRIVER_MODE_2_VOLT_CURR_2		0x30
#define DRIVER_MODE_2_VOLT_CURR_3		0x3B

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Driver mode 3 - communication
 * Default:
 * RS485:CAFR 
 * CAN:CAFC
 * Attribute = 32U,RO
 *   Unit = [ASCII]
 */
 
#define DRIVER_MODE_3_COMMUNITY			0x30003C
#define DRIVER_MODE_3_COMMUNITY_1		0x00
#define DRIVER_MODE_3_COMMUNITY_2		0x30
#define DRIVER_MODE_3_COMMUNITY_3		0x3C

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Driver mode 4 – software version
 * Default:
 * For 7Nm motor:ASL3 = 0x41534C33
 * For 10Nm motor:ASM4 = 0x41536D34
 * For 15Nm motor:ASM5 = 0x41536D35
 * Attribute = 32U,RO
 *   Unit = [ASCII]
 */
 
#define DRIVER_MODE_4_SOFTWARE_VER			0x30003D
#define DRIVER_MODE_4_SOFTWARE_VER_1		0x00
#define DRIVER_MODE_4_SOFTWARE_VER_2		0x30
#define DRIVER_MODE_4_SOFTWARE_VER_3		0x3D

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Firmware date
 * Format:20190114
 * Year: 2019
 * Month: 01
 * Day: 14
 * Attribute = 32U,RO
 *   Unit = [DEC]
 */
 
#define FIRMWARE_DATE								0x2500F1 
#define FIRMWARE_DATE_1							0x00 
#define FIRMWARE_DATE_2							0x25 
#define FIRMWARE_DATE_3 						0xF1 

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Hardware version
 * Attribute = 32U,RO
 *   Unit = [ASCII]
 */
 
#define	HARDWARE_VER								0x2500F3
#define	HARDWARE_VER_1							0x00
#define	HARDWARE_VER_2							0x25
#define	HARDWARE_VER_3							0xF3

/* DRIVER ATTRIBUTE END */

/* ADDITIONAL FUNCTIONS START */

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Sstop function
 * 0:Disable
 * 1:Enable
 * Default:0
 * It is used to limit driver output current when motor is in zero speed.
 * Attribute = 08U,RW,S5
 *    Unit = [DEC]
 */
 
#define SSTOP_FUNCTION							0x500020
#define SSTOP_FUNCTION_1						0x00
#define SSTOP_FUNCTION_2						0x50
#define SSTOP_FUNCTION_3						0x20 
#define SSTOP_FUNCTION_DISABLE			0
#define SSTOP_FUNCTION_ENABLE				1	
#define UART_SSTOP_FUNCTION					0x802F
#define UART_SSTOP_FUNCTION_H				0x80
#define UART_SSTOP_FUNCTION_L				0x2F
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Sstop current limit
 * U[y，x]：
 * [DEC]=[Arms]*1.414*2048*256/I_MAX
 * Note:L2DB4830 series，I_MAX=33；
 * Default：
 * L2DB4830 series：10485 (0.467Arms)
 * Attribute = 32U,RW,S5
 *    Unit = [DEC]
 */
 
#define SSTOP_CURRENT_LIMIT					0x500028
#define SSTOP_CURRENT_LIMIT_1				0x00
#define SSTOP_CURRENT_LIMIT_2				0x50
#define SSTOP_CURRENT_LIMIT_3				0x28
#define UART_SSTOP_CURRENT_LIMIT		0x8028
#define UART_SSTOP_CURRENT_LIMIT_H	0x80
#define UART_SSTOP_CURRENT_LIMIT_L	0x28
// need to check for I_max value and Arms value

/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * S curve start point at decelerating
 * U[y,x]:
 * [DEC]=([rpm]*512*[Resolution])/1875;
 * [Resolution]Default:4096
 * Default:5rpm
 * Attribute = 32U,RW,S5
 *    Unit = [DEC]
 */
 
#define S_CURVE_START_DECELERATE					0x500002
#define S_CURVE_START_DECELERATE_1				0x00
#define S_CURVE_START_DECELERATE_2				0x50
#define S_CURVE_START_DECELERATE_3				0x02
#define UART_S_CURVE_START_DECELERATE			0x8002
#define UART_S_CURVE_START_DECELERATE_H		0x80
#define UART_S_CURVE_START_DECELERATE_L		0x02
/**
 * @brief CAN Object address [16bits][8bits] (Index SubIndex)
 * Time for S curve 
 * Default:64
 * Attribute  = 16U,RW,S5
 *    Unit = [DEC]
 */
 
#define TIME_S_CURVE								0x500004
#define TIME_S_CURVE_1							0x00
#define TIME_S_CURVE_2							0x50
#define TIME_S_CURVE_3							0x04
#define UART_TIME_S_CURVE						0x8004
#define UART_TIME_S_CURVE_H					0x80
#define UART_TIME_S_CURVE_L					0x04
/* ADDITIONAL FUNCTIONS END */

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * Simple PDO Function
  *  Default = 0 [ Disable TXPDO1
  *  Attribute = 08U,RW
  *     Unit   = [DEC]
  */
	
#define SIMPLE_PDO									0x470001
#define SIMPLE_PDO_1ST_BYTE					0x00
#define SIMPLE_PDO_2ND_BYTE					0x47
#define SIMPLE_PDO_3RD_BYTE					0x01
#define SIMPLE_PDO_ENABLE						1U
#define SIMPLE_PDO_DISABLE					0U

/**
  * @brief CAN Object Address  [16bits][8bits] ( Index, subindex )
  * TX-PDO1 prohibit time
  *  Default = 10mS
  *  Attribute = 16U,RW
  *     Unit   = [mS]
  */

#define TX_PDO1											0x180003
#define TX_PDO1_1ST_BYTE						0x00
#define TX_PDO1_2ND_BYTE						0x18
#define TX_PDO1_3RD_BYTE						0x03

/* Sending CMD */
#define SEND_ONE_BYTE								0x2F				// Write mode
#define SEND_TWO_BYTE								0x2B				// Write mode
#define SEND_FOURBYTE								0x23				// Write mode
#define SEND_REQUEST								0x40				// Read mode

/* Receiving CMD */
#define RECEIVE_ONE_BYTE						0x4F
#define RECEIVE_TWO_BYTE						0x4B
#define RECEIVE_FOURBYTE						0x43

#define RECEIVE_ERROR								0x80
#define RECEIVE_SUCCESS							0x60

/* Untest APIs ( function prototypes ) */
void ___ROM_LSDB_PREPARE(CAN_HandleTypeDef *p_hcan1);
void CAN1_FILTER_Config(CAN_HandleTypeDef *p_hcan1);

/*** SPEED MODE START ***/
/* SPEED_MODE_WITH_ACCEL_DECEL , SPEED_MODE, TORQUE_MODE, POSITION_MODE */
void setOperatingMode(CAN_HandleTypeDef *p_hcan1, int8_t mode);

/* CONTROL_WORD_ENABLE , CONTROL_WORD_DISABLE , CONTROL_WORD_CLEAR */
void enableMotorRight(CAN_HandleTypeDef *p_hcan1, int16_t flag);
void enableMotorLeft(CAN_HandleTypeDef *p_hcan1, int16_t flag);

/* DRIVER_STATUS_NORMAL , DRIVER_STATUS_ERROR  */
void getDriverStatus(CAN_HandleTypeDef *p_hcan1);

/* EMERGENCY_STOP_ENABLE , EMERGENCY_STOP_DISABLE */
void EmergencyMode(CAN_HandleTypeDef *p_hcan1, uint8_t flag);
void decel_in_emergency_stop(CAN_HandleTypeDef *p_hcan1, uint32_t flag);

/* Acceleration */
void setAccel(CAN_HandleTypeDef *p_hcan1,uint32_t rev_per_sec_sqr);
uint32_t calculateAccel (uint32_t rev_per_sec_sqr);
void transmitAccel(CAN_HandleTypeDef *p_hcan1, uint32_t flag);

/* Deceleration */
uint32_t calculateDecel (uint32_t rev_per_sec_sqr);
void setDecel(CAN_HandleTypeDef *p_hcan1,uint32_t rev_per_sec_sqr);
void transmitDecel(CAN_HandleTypeDef *p_hcan1, uint32_t flag);

/* be care, input are signed params */
void setTargetVelocityRpmRight(CAN_HandleTypeDef *p_hcan1, int16_t rpm);
void setTargetVelocityRpmLeft(CAN_HandleTypeDef *p_hcan1, int16_t rpm);
void setTargetVelocityDEC(CAN_HandleTypeDef *p_hcan1, int32_t dec);

/* */
void max_following_error(CAN_HandleTypeDef *p_hcan1, uint32_t flag);

/* */
void position_loop_speed_feedforward(CAN_HandleTypeDef *p_hcan1, int16_t flag);

/* */
void set_position_propotion_gain(CAN_HandleTypeDef *p_hcan1, int16_t flag);

/* */
void set_speed_propotion_gain(CAN_HandleTypeDef *p_hcan1, uint16_t flag);

/* */
void set_speed_integration_gain(CAN_HandleTypeDef *p_hcan1, uint16_t flag);
/*** SPEED MODE END ***/

/* SIMPLE_PDO_ENABLE , SIMPLE_PDO_DISABLE */
void enableTenMilliSecondLoop(CAN_HandleTypeDef *p_hcan1, uint8_t flag);

/* MAXIMUM SPEED SETTING maximum=120rpm */
void setMaxRPM(CAN_HandleTypeDef *p_hcan1, uint8_t rpm);

/* Radian per second <=> RPM */
int16_t rdsToRPM (double rds);
double rpmToRds (int16_t rpm);

/* Speed Related Funtions */
void setActualSpeedSamplingCycle(CAN_HandleTypeDef *p_hcan1, uint16_t milliSec);
void getActualRpmRight(CAN_HandleTypeDef *p_hcan1);
void getActualRpmLeft(CAN_HandleTypeDef *p_hcan1);
void disableMotors(CAN_HandleTypeDef *p_hcan1);
void clearMotors(CAN_HandleTypeDef *p_hcan1);


/* Position Related Functions */
void clearActualPostion(CAN_HandleTypeDef *p_hcan1);

/* Noise Reduction */
void enableNoiseReductionatZeroSpeed (CAN_HandleTypeDef *p_hcan1);

/* TO DO */ 
// check port setting()
//void getActualDCBusVoltage(CAN_HandleTypeDef *p_hcan1);

// check communication parameters()
// check parameter storage()
// check driver attribute()



#endif

