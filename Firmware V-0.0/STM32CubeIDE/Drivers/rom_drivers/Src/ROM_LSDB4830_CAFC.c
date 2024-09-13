#include "ROM_LSDB4830_CAFC.h"
#include "tim.h"
#include "main.h"

uint32_t txMailbox;
CAN_TxHeaderTypeDef txHeader;

uint8_t tx_data[8] = {0};
//uint8_t rx_data[8] = {0}; 

extern uint8_t speed_limit;

void ___ROM_LSDB_PREPARE(CAN_HandleTypeDef *p_hcan1)
{ 
	/* Now You can transmit/receive */
	txHeader.DLC = 8;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	
	/* Servo hub related */
	clearMotors(p_hcan1);
	HAL_Delay(1);
	
	disableMotors(p_hcan1);
	HAL_Delay(1);
	
	clearActualPostion(p_hcan1);
	HAL_Delay(1);
	
	/* Acceleration 2 rad/s^2 */
	setAccel(p_hcan1, 2);
	HAL_Delay(1);

	/* Deceleration 2 rad/s^2 */
	setDecel(p_hcan1, 2);
	HAL_Delay(1);
	
	enableMotorLeft(p_hcan1,CONTROL_WORD_ENABLE);
	HAL_Delay(1);
	
	enableMotorRight(p_hcan1,CONTROL_WORD_ENABLE);
	HAL_Delay(1);
	
	/* These object must be after Enable motors. */
	/* Default Speed Mode */
	setOperatingMode(p_hcan1, SPEED_MODE_WITH_ACCEL_DECEL); // response time 140us
	HAL_Delay(1);
	
	setActualSpeedSamplingCycle(p_hcan1, 10);
	HAL_Delay(1);
	
	setMaxRPM(p_hcan1, speed_limit);
	HAL_Delay(1);
	
	setTargetVelocityRpmRight(p_hcan1,0);
	HAL_Delay(1);
	
	setTargetVelocityRpmLeft(p_hcan1,0);
	HAL_Delay(1);
	
	
	
	#ifdef USE_PDO
		enableTenMilliSecondLoop(p_hcan1,SIMPLE_PDO_ENABLE);
	#endif
	
	//enableNoiseReductionatZeroSpeed(p_hcan1);
	//HAL_Delay(1);
	
	/* Test Run 
	setTargetVelocityRPM(p_hcan1,50);
	HAL_Delay(5000);
	setTargetVelocityRPM(p_hcan1,0);
	*/
	
	/* Test Run Receive */
	//getActualRpmRight(p_hcan1);
	//getActualRpmLeft(p_hcan1);
}



/* SPEED MODE FUNCTION START */
void setOperatingMode(CAN_HandleTypeDef *p_hcan1, int8_t op_mode)
{
	txHeader.StdId = RIGHT_MOTOR;   
	tx_data[0] = SEND_ONE_BYTE;
	
	tx_data[1] = OPERATION_MODE_1ST_BYTE;
	tx_data[2] = OPERATION_MODE_2ND_BYTE;
	tx_data[3] = OPERATION_MODE_3RD_BYTE;
	
	tx_data[4] = op_mode;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
	//for left motor 0x602
	txHeader.StdId = LEFT_MOTOR;
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}
void enableMotorRight(CAN_HandleTypeDef *p_hcan1, int16_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	
	tx_data[1] = CONTROL_WORD_1ST_BYTE;
	tx_data[2] = CONTROL_WORD_2ND_BYTE;
	tx_data[3] = CONTROL_WORD_3RD_BYTE;
	
	tx_data[4] = flag & 0xFF;
	tx_data[5] = (flag >> 8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}
void enableMotorLeft(CAN_HandleTypeDef *p_hcan1, int16_t flag)
{
	txHeader.StdId = LEFT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	
	tx_data[1] = CONTROL_WORD_1ST_BYTE;
	tx_data[2] = CONTROL_WORD_2ND_BYTE;
	tx_data[3] = CONTROL_WORD_3RD_BYTE;
	
	tx_data[4] = flag & 0xFF;
	tx_data[5] = (flag >> 8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
}



void getDriverStatus(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_REQUEST;
	tx_data[1] = DRIVER_STATUS_1ST_BYTE;
	tx_data[2] = DRIVER_STATUS_2ND_BYTE;
	tx_data[3] = DRIVER_STATUS_3RD_BYTE;
	
	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void EmergencyMode(CAN_HandleTypeDef *p_hcan1, uint8_t flag)
{
	txHeader.StdId = RIGHT_MOTOR;   
	tx_data[0] = SEND_ONE_BYTE;
	tx_data[1] = EMERGENCY_STOP_1ST_BYTE;
	tx_data[2] = EMERGENCY_STOP_2ND_BYTE;
	tx_data[3] = EMERGENCY_STOP_3RD_BYTE;
	
	tx_data[4] = flag;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
	
	delay_us(200);
	txHeader.StdId = LEFT_MOTOR;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void transmitAccel(CAN_HandleTypeDef *p_hcan1, uint32_t flag)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_FOURBYTE;
	tx_data[1] = ACCELERATION_1ST_BYTE;
	tx_data[2] = ACCELERATION_2ND_BYTE;
	tx_data[3] = ACCELERATION_3RD_BYTE;
	
	tx_data[4] = flag & 0xFF;
	tx_data[5] = (flag >> 8) & 0xFF;
	tx_data[6] = (flag >> 16) & 0xFF;
	tx_data[7] = (flag >> 24) & 0xFF;
	
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
	// Left
	txHeader.StdId = LEFT_MOTOR;
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}
void transmitDecel(CAN_HandleTypeDef *p_hcan1, uint32_t flag)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_FOURBYTE;
	tx_data[1] = DECELERATION_1ST_BYTE;
	tx_data[2] = DECELERATION_2ND_BYTE;
	tx_data[3] = DECELERATION_3RD_BYTE;
	
	tx_data[4] = flag & 0xFF;
	tx_data[5] = (flag >> 8) & 0xFF;
	tx_data[6] = (flag >> 16) & 0xFF;
	tx_data[7] = (flag >> 24) & 0xFF;
	
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
	// Left
	txHeader.StdId = LEFT_MOTOR;
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}

void decel_in_emergency_stop(CAN_HandleTypeDef *p_hcan1, uint32_t flag)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_FOURBYTE;
	tx_data[1] = DECELERATION_IN_EMERGENCY_1;
	tx_data[2] = DECELERATION_IN_EMERGENCY_2;
	tx_data[3] = DECELERATION_IN_EMERGENCY_3;
	
	tx_data[4] = flag & 0xFF;
	tx_data[5] = (flag >> 8) & 0xFF;
	tx_data[6] = (flag >> 16) & 0xFF;
	tx_data[7] = (flag >> 24) & 0xFF;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}

void setTargetVelocityRpmRight(CAN_HandleTypeDef *p_hcan1,int16_t rpm)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = DESIRE_VEL_RPM_1ST_BYTE;
	tx_data[2] = DESIRE_VEL_RPM_2ND_BYTE;
	tx_data[3] = DESIRE_VEL_RPM_3RD_BYTE;
	
	tx_data[4] = rpm & 0xFF;
	tx_data[5] = (rpm >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox); // need hal ok
}
void setTargetVelocityRpmLeft(CAN_HandleTypeDef *p_hcan1,int16_t rpm)
{
	txHeader.StdId = LEFT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = DESIRE_VEL_RPM_1ST_BYTE;
	tx_data[2] = DESIRE_VEL_RPM_2ND_BYTE;
	tx_data[3] = DESIRE_VEL_RPM_3RD_BYTE;
	
	rpm *= -1;
	
	tx_data[4] = rpm & 0xFF;
	tx_data[5] = (rpm >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}

void setTargetVelocityDEC(CAN_HandleTypeDef *p_hcan1,int32_t dec)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_FOURBYTE;
	tx_data[1] = DESIRE_VEL_DEC_1ST_BYTE;
	tx_data[2] = DESIRE_VEL_DEC_2ND_BYTE;
	tx_data[3] = DESIRE_VEL_DEC_3RD_BYTE;
	
	//int32_t target_rpm = dec * rpm_constant; // Need to Fix!!!!!
	//tx_data[4] = target_rpm & 0xFF;
	//tx_data[5] = (target_rpm >>  8) & 0xFF;
	//tx_data[6] = (target_rpm >> 16) & 0xFF;
	//tx_data[7] = (target_rpm >> 24) & 0xFF;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}

void max_following_error(CAN_HandleTypeDef *p_hcan1, uint32_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_FOURBYTE;
	tx_data[1] = MAX_FOLLOWING_ERR_1ST_BYTE;
	tx_data[2] = MAX_FOLLOWING_ERR_2ND_BYTE;
	tx_data[3] = MAX_FOLLOWING_ERR_3RD_BYTE;
	
	tx_data[4] =  flag & 0xFF;
	tx_data[5] = (flag >>  8) & 0xFF;
	tx_data[6] = (flag >> 16) & 0xFF;
	tx_data[7] = (flag >> 24) & 0xFF;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void position_loop_speed_feedforward(CAN_HandleTypeDef *p_hcan1, int16_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = POS_LOOP_SPEED_FF_1ST_BYTE;
	tx_data[2] = POS_LOOP_SPEED_FF_2ND_BYTE;
	tx_data[3] = POS_LOOP_SPEED_FF_3RD_BYTE;
	
	tx_data[4] =  flag & 0xFF;
	tx_data[5] = (flag >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void set_position_propotion_gain(CAN_HandleTypeDef *p_hcan1, int16_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = PROPOTION_GAIN_IN_POS_1;
	tx_data[2] = PROPOTION_GAIN_IN_POS_2;
	tx_data[3] = PROPOTION_GAIN_IN_POS_3;
	
	tx_data[4] =  flag & 0xFF;
	tx_data[5] = (flag >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void set_speed_propotion_gain(CAN_HandleTypeDef *p_hcan1, uint16_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = PROPOTION_GAIN_IN_SPEED_1;
	tx_data[2] = PROPOTION_GAIN_IN_SPEED_1;
	tx_data[3] = PROPOTION_GAIN_IN_SPEED_1;
	
	tx_data[4] =  flag & 0xFF;
	tx_data[5] = (flag >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void set_speed_integration_gain(CAN_HandleTypeDef *p_hcan1, uint16_t flag)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = INTEGRATOR_GAIN_IN_SPEED_1;
	tx_data[2] = INTEGRATOR_GAIN_IN_SPEED_1;
	tx_data[3] = INTEGRATOR_GAIN_IN_SPEED_1;
	
	tx_data[4] =  flag & 0xFF;
	tx_data[5] = (flag >>  8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
/* SPEED MODE FUNCTION END */


/* SIMPLE_PDO_ENABLE , SIMPLE_PDO_DISABLE */
void enableTenMilliSecondLoop(CAN_HandleTypeDef *p_hcan1, uint8_t flag)
{
	txHeader.StdId = RIGHT_MOTOR;   
	tx_data[0] = SEND_ONE_BYTE;
	tx_data[1] = SIMPLE_PDO_1ST_BYTE;
	tx_data[2] = SIMPLE_PDO_2ND_BYTE;
	tx_data[3] = SIMPLE_PDO_3RD_BYTE;
	
	tx_data[4] = flag;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
	
	txHeader.StdId = LEFT_MOTOR;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}

/* MAXIMUM SPEED SETTING */
void setMaxRPM(CAN_HandleTypeDef *p_hcan1,uint8_t rpm)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	tx_data[1] = MAX_SPEED_RPM_1ST_BYTE;
	tx_data[2] = MAX_SPEED_RPM_2ND_BYTE;
	tx_data[3] = MAX_SPEED_RPM_3RD_BYTE;
	
	tx_data[4] = rpm;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
	txHeader.StdId = LEFT_MOTOR;
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}

/* RPM to rad/s conversion */
/* rad/s to RPM conversion */

int16_t rdsToRPM (double rds)
{
	return (int16_t)(rds*9.549297);
}

double rpmToRds (int16_t rpm)
{
	return (double)(rpm/9.549297);
}

/* Acceleration & Deceleration */
uint32_t calculateAccelDecel (uint32_t rev_per_sec_sqr)
{
	return (uint32_t)(rev_per_sec_sqr * 67.108864);
}
void setAccel(CAN_HandleTypeDef *p_hcan1,uint32_t rev_per_sec_sqr)
{
	uint32_t flag = calculateAccelDecel(rev_per_sec_sqr);
	transmitAccel(p_hcan1,flag);
}
void setDecel(CAN_HandleTypeDef *p_hcan1,uint32_t rev_per_sec_sqr)
{
	uint32_t flag = calculateAccelDecel(rev_per_sec_sqr);
	transmitDecel(p_hcan1,flag);
}

/* Speed Related functions */
void setActualSpeedSamplingCycle(CAN_HandleTypeDef *p_hcan1, uint16_t milliSec)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_TWO_BYTE;
	
	tx_data[1] = SAMPLE_CYCLE_ACTUAL_SPEED_1Byte;
	tx_data[2] = SAMPLE_CYCLE_ACTUAL_SPEED_2Byte;
	tx_data[3] = SAMPLE_CYCLE_ACTUAL_SPEED_3Byte;
	
	tx_data[4] = milliSec & 0xFF;
	tx_data[5] = (milliSec >> 8) & 0xFF;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	// LEFT
	txHeader.StdId = LEFT_MOTOR;
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}

void getActualRpmRight(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR; 
	tx_data[0] = SEND_REQUEST;
	
	tx_data[1] = ACTUAL_SPEED_RPM_1Byte;
	tx_data[2] = ACTUAL_SPEED_RPM_2Byte;
	tx_data[3] = ACTUAL_SPEED_RPM_3Byte;
	
	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
	// rx cmd 60 ok, 80 failed;
}
void getActualRpmLeft(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = LEFT_MOTOR;
	tx_data[0] = SEND_REQUEST;
	
	tx_data[1] = ACTUAL_SPEED_RPM_1Byte;
	tx_data[2] = ACTUAL_SPEED_RPM_2Byte;
	tx_data[3] = ACTUAL_SPEED_RPM_3Byte;
	
	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
	// rx cmd 60 ok, 80 failed;
}

void disableMotors(CAN_HandleTypeDef *p_hcan1)
{
	/* Servo Stop */
	enableMotorLeft(p_hcan1,CONTROL_WORD_DISABLE);
	//-->delay_us(200);	
	enableMotorRight(p_hcan1,CONTROL_WORD_DISABLE);
	//-->delay_us(200);
}
void clearMotors(CAN_HandleTypeDef *p_hcan1)
{
	enableMotorLeft(p_hcan1,CONTROL_WORD_CLEAR);
	//-->delay_us(200);	
	enableMotorRight(p_hcan1,CONTROL_WORD_CLEAR);
	//-->delay_us(200);
}
/* Position Related Functions */
void clearActualPostion(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;   
	tx_data[0] = SEND_ONE_BYTE;
	tx_data[1] = CLEAR_ACTUAL_POSITION_1Byte;
	tx_data[2] = CLEAR_ACTUAL_POSITION_2Byte;
	tx_data[3] = CLEAR_ACTUAL_POSITION_3Byte;
	
	tx_data[4] = 0x01;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
	
	txHeader.StdId = LEFT_MOTOR;
	#ifdef CAN_DEBUG
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
	
	// rx cmd 60 ok, 80 failed;
	if ( HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox) != HAL_OK )
	{
		CAN_Error_Handler();
	}
	
	// Polling ( Continuous checking ) for Transmit status
	while( HAL_CAN_IsTxMessagePending(p_hcan1, txMailbox) )
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
		#endif
	}
}
/* Noise Recduction */
void enableNoiseReductionatZeroSpeed (CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;   
	tx_data[0] = SEND_ONE_BYTE;
	tx_data[1] = NOISE_REDUCTION_1Byte;
	tx_data[2] = NOISE_REDUCTION_1Byte;
	tx_data[3] = NOISE_REDUCTION_1Byte;
	
	tx_data[4] = NOISE_REDUCTION_ENABLE ;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
	
	//txHeader.StdId = LEFT_MOTOR;
	//HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
	
/*Ampere,Voltage*/
void getActualCurrent(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_REQUEST;

	tx_data[1] = ACTUAL_CURRENT_Iq_1;
	tx_data[2] = ACTUAL_CURRENT_Iq_2;
	tx_data[3] = ACTUAL_CURRENT_Iq_3;

	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void getMotorIItCurrent(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_REQUEST;

	tx_data[1] = MOTOR_ACUTAL_IIt_CURRENT_1;
	tx_data[2] = MOTOR_ACUTAL_IIt_CURRENT_2;
	tx_data[3] = MOTOR_ACUTAL_IIt_CURRENT_3;

	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
void getActualDCVoltage(CAN_HandleTypeDef *p_hcan1)
{
	txHeader.StdId = RIGHT_MOTOR;
	tx_data[0] = SEND_REQUEST;

	tx_data[1] = ACTUAL_DC_VOLTAGE_1;
	tx_data[2] = ACTUAL_DC_VOLTAGE_2;
	tx_data[3] = ACTUAL_DC_VOLTAGE_3;

	tx_data[4] = 0x00;
	tx_data[5] = 0x00;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
	HAL_CAN_AddTxMessage(p_hcan1, &txHeader, tx_data, &txMailbox);
}
