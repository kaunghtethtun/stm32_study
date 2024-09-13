/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(?) COPYLEFT 2023		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_VARIABLES_H
#define __ROM_VARIABLES_H

#include "stm32f4xx.h"

/* robot to pc */
//int32_t left_wheel_ticks;
//int32_t right_wheel_ticks;
//double yaw_radian;
//double quart[4];
//int8_t Estop_status;
int8_t battery_status;

/* pc to robot */
//double left_desire_rds;
//double right_desire_rds;
uint8_t speed_limit;
//int8_t led_cmd[4];

/* USB */


/* CAN1 */
CAN_RxHeaderTypeDef rxHeader = {0};
uint8_t CAN_rxData[8];

/* LSDB4830 */
double current_constant = 96.5290;
double actual_current_Iq = 0;
//double rpm_constant = 11335.956; // rpm or DEC command

int16_t right_actual_rpm;
int16_t left_actual_rpm;

int16_t right_desire_rpm;
int16_t left_desire_rpm; 

int32_t right_actual_position;
int32_t left_actual_position;

/* Variables for General usage */
int16_t counts = 0;

/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  ROM_OK       = 0x00U,
  ROM_ERROR    = 0x01U,
  ROM_BUSY     = 0x02U,
  ROM_TIMEOUT  = 0x03U
} ROM_StatusTypeDef;
#endif
