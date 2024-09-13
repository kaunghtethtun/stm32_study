/*
 * rom_communication.h
 *
 *  Created on: Aug 3, 2024
 *      Author: Pyae Soan Aung
 */

#ifndef APPLICATION_USER_CORE_ROM_COMMUNICATION_H_
#define APPLICATION_USER_CORE_ROM_COMMUNICATION_H_

#define MCU

/* our protocol */
// [ rar lar rec lec rdr ldr free e1234567 vol amp crc_check "\r" "\n" ]   // portable
//	  2   2   4    4  2   2   1      1      1   4   4          1    1 = 29 B
#ifndef MCU
#include <cstdint>
#include <cstring>
#endif

int8_t ROM_checksum(int32_t *data)
{
	int32_t tmp = (data[0]+data[1]+data[2]+data[3]+data[4]+data[5])& 0x000000FF;
	int8_t tmp2 = (int8_t)tmp;
	return tmp2;
}

struct ROM_COMMUNICATION {
	int16_t right_actual_rpm;			// rar
	int16_t left_actual_rpm;			// lar

	int32_t right_encoder_count;		// rec  -2,147,483,64
	int32_t left_encoder_count;			// lec

	int16_t right_desire_rpm;			// rdr
	int16_t left_desire_rpm;			// ldr

	int8_t free;
	int8_t e1234567;					// estop bit, led 1 bit, .... , led 7 bit

	int8_t volt;
	float ampere;						// may be float

	int8_t checksum;
	int8_t calculated_checksum;

	uint8_t buffer[30];
};

struct e1234567_status {
	_Bool estop_status;
	_Bool led1_status;
	_Bool led2_status;
	_Bool led3_status;
	_Bool led4_status;
	_Bool led5_status;
	_Bool led6_status;
	_Bool led7_status;
};

#ifdef MCU
void
encodeBuffer(int16_t *rar, int16_t *lar,
		int32_t *rec, int32_t *lec,
		int8_t *free, int8_t *e1234567,
		int8_t *volt, float *amp,
		uint8_t *buffer )
{
	// Copy the integer values into the buffer (assuming little-endian system)
	buffer[0] = (uint8_t)(   *(rar) & 0xFF );
	buffer[1] = (uint8_t)( ( *(rar) >> 8 )  & 0xFF );

	buffer[2] = (uint8_t)(   *(lar) & 0xFF );
	buffer[3] = (uint8_t)( ( *(lar) >> 8 )  & 0xFF );

	buffer[4] = (uint8_t)(   *(rec) & 0xFF );
	buffer[5] = (uint8_t)( ( *(rec) >> 8 )  & 0xFF );
	buffer[6] = (uint8_t)( ( *(rec) >> 16 ) & 0xFF );
	buffer[7] = (uint8_t)( ( *(rec) >> 24 ) & 0xFF );

	buffer[8]  = (uint8_t)(  *(lec) & 0xFF );
	buffer[9]  = (uint8_t)(( *(lec) >> 8 )  & 0xFF );
	buffer[10] = (uint8_t)(( *(lec) >> 16 ) & 0xFF );
	buffer[11] = (uint8_t)(( *(lec) >> 24 ) & 0xFF );

	/* rdr နဲ့ ldr ကို pc က ဖမ်းစရာမလို */
	buffer[12] = (uint8_t)0xff; buffer[13] = (uint8_t)0xff;
	buffer[14] = (uint8_t)0xff; buffer[15] = (uint8_t)0xff;

	buffer[16] = (uint8_t)*(free) ;

	buffer[17] = (uint8_t)*(e1234567);

	buffer[18] = (uint8_t)*(volt);

	// float to byte array
	uint8_t byte_arr[4];
	memcpy(byte_arr, amp, 4);
	buffer[19] = byte_arr[0];
	buffer[20] = byte_arr[1];
	buffer[21] = byte_arr[2];
	buffer[22] = byte_arr[3];

	/* CALCULATE CHECKSUM */
		int32_t data[6]; //24bytes
		data[0] = buffer[0] +(buffer[1] <<8)+(buffer[2] <<16)+(buffer[3] <<24);
		data[1] = buffer[4] +(buffer[5] <<8)+(buffer[6] <<16)+(buffer[7] <<24);
		data[2] = buffer[8] +(buffer[9] <<8)+(buffer[10]<<16)+(buffer[11]<<24);
		data[3] = buffer[12]+(buffer[13]<<8)+(buffer[14]<<16)+(buffer[15]<<24);
		data[4] = buffer[16]+(buffer[17]<<8)+(buffer[18]<<16)+(buffer[19]<<24);
		data[5] = buffer[20]+(buffer[21]<<8)+(buffer[22]<<16)+(0x0000    <<24);
		int8_t checksum_= ROM_checksum(data);

	buffer[23] = (uint8_t)checksum_;

	buffer[24] = (uint8_t)13; //"\r";
	buffer[25] = (uint8_t)10; //"\n";
}

void
decodeBuffer(uint8_t* arr, struct ROM_COMMUNICATION *my_struct)
{

	my_struct->right_actual_rpm = (arr[0] + ( arr[1] << 8 ));

	my_struct->left_actual_rpm  = arr[2] + ( arr[3] << 8 );

	my_struct->right_encoder_count = arr[4] + ( arr[5]<<8) + (arr[6]<<16) + (arr[7]<<24);

	my_struct->left_encoder_count = arr[8] + ( arr[9]<<8) + (arr[10]<<16) + (arr[11]<<24);

	/* get rdr and ldr from pc */
	my_struct->right_desire_rpm = arr[12] + ( arr[13] << 8 );
	my_struct->left_desire_rpm  = arr[14] + ( arr[15] << 8 );

	my_struct->free = (int8_t)arr[16];

	my_struct->e1234567 = (int8_t)arr[17];
//	uint8_t tmp = arr[17];
//	e123->estop_status = ( (uint8_t)tmp & 0b10000000) >> 7;
//	e123->led1_status  = ( (uint8_t)tmp & 0b01000000) >> 6;
//	e123->led2_status  = ( (uint8_t)tmp & 0b00100000) >> 5;
//	e123->led3_status  = ( (uint8_t)tmp & 0b00010000) >> 4;
//	e123->led4_status  = ( (uint8_t)tmp & 0b00001000) >> 3;
//	e123->led5_status  = ( (uint8_t)tmp & 0b00000100) >> 2;
//	e123->led6_status  = ( (uint8_t)tmp & 0b00000010) >> 1;
//	e123->led7_status  = ( (uint8_t)tmp & 0b00000001);

	my_struct->volt = (int8_t)arr[18];

	uint8_t tmp[4] = { arr[19],arr[20], arr[21], arr[22] };
	memcpy(&my_struct->ampere, tmp, 4);

	my_struct->checksum = arr[23];

	/* CHECKSUM CALCULATE */
		int32_t data[6]; //24bytes
		data[0] =  arr[0]+(arr[1] <<8)+(arr[2] <<16)+(arr[3] <<24);
		data[1] =  arr[4]+(arr[5] <<8)+(arr[6] <<16)+(arr[7] <<24);
		data[2] =  arr[8]+(arr[9] <<8)+(arr[10]<<16)+(arr[11]<<24);
		data[3] = arr[12]+(arr[13]<<8)+(arr[14]<<16)+(arr[15]<<24);
		data[4] = arr[16]+(arr[17]<<8)+(arr[18]<<16)+(arr[19]<<24);
		data[5] = arr[20]+(arr[21]<<8)+(arr[22]<<16)+(0x0000 <<24);

		my_struct->calculated_checksum = ROM_checksum(data);

	// \r\n တို့ကို တော့ decode လုပ်ဖို့ မလို
	// arr[27]="\r"; arr[28]="\n";
}
#else
void
encodeBuffer(struct ROM_COMMUNICATION *my_struct,
		struct e1234567_status *e123)
{
	// my_struct->buffer[0] = 0xff; my_struct->buffer[1]= 0xff;

	// my_struct->buffer[2] = 0xff; my_struct->buffer[3]= 0xff;

	// my_struct->buffer[4]=0xff;my_struct->buffer[5]=0xff;my_struct->buffer[6]=0xff;my_struct->buffer[7]=0xff;

	// my_struct->buffer[8]=0xff;my_struct->buffer[9]=0xff;my_struct->buffer[10]=0xff;my_struct->buffer[11]=0xff;

	// my_struct->buffer[12] = (uint8_t)(   my_struct->right_desire_rpm & 0xFF );
	// my_struct->buffer[13] = (uint8_t)( ( my_struct->right_desire_rpm >> 8 ) & 0xFF );

	// my_struct->buffer[14] = (uint8_t)(   my_struct->left_desire_rpm & 0xFF );
	// my_struct->buffer[15] = (uint8_t)( ( my_struct->left_desire_rpm >> 8 ) & 0xFF );

	// my_struct->buffer[16] = my_struct->free;

	/* struct ထဲကယူပြီးပို့သင့်တယ်။ mcu က ပြန်လာတဲ့ e1234567 ကိုတော့ struct ထဲပို့သင့် မသင့် စဥ်းစားပါ။ */
	// my_struct->buffer[17] = 0;

	/* တကယ်တော့ ဒီနေရာမှာ volt မပို့ပဲ အခြားဟာ ပို့လို့ရနေပါတယ်။ */
	// my_struct->buffer[18] = 0xff;

	/* တကယ်တော့ ဒီနေရာမှာ ampere မပို့ပဲ အခြားဟာ ပို့လို့ရနေပါတယ်။ */
	// my_struct->buffer[19] = 0xff;	//(uint8_t)(   *(amp) & 0xFF );
	// my_struct->buffer[20] = 0xff;	//(uint8_t)( ( *(amp) >> 8 )  & 0xFF );
	// my_struct->buffer[21] = 0xff;	//(uint8_t)( ( *(amp) >> 16 ) & 0xFF );
	// my_struct->buffer[22] = 0xff;	//(uint8_t)( ( *(amp) >> 24 ) & 0xFF );

	/* CALCULATE CHECKSUM */
	// 	int32_t data[6];
	// 	data[0] = my_struct->buffer[0] +(my_struct->buffer[1] <<8)+(my_struct->buffer[2] <<16)+(my_struct->buffer[3] <<24);
	// 	data[1] = my_struct->buffer[4] +(my_struct->buffer[5] <<8)+(my_struct->buffer[6] <<16)+(my_struct->buffer[7] <<24);
	// 	data[2] = my_struct->buffer[8] +(my_struct->buffer[9] <<8)+(my_struct->buffer[10]<<16)+(my_struct->buffer[11]<<24);
	// 	data[3] = my_struct->buffer[12]+(my_struct->buffer[13]<<8)+(my_struct->buffer[14]<<16)+(my_struct->buffer[15]<<24);
	// 	data[4] = my_struct->buffer[16]+(my_struct->buffer[17]<<8)+(my_struct->buffer[18]<<16)+(my_struct->buffer[19]<<24);
	// 	data[5] = my_struct->buffer[20]+(my_struct->buffer[21]<<8)+(my_struct->buffer[22]<<16)+(0x0000    <<24);
	// 	int8_t checksum_= ROM_checksum(data);

	// my_struct->buffer[23] = checksum_;
	my_struct->checksum = (my_struct->right_desire_rpm+my_struct->left_desire_rpm) & 0xff;

	/* "\r\n" */
	// my_struct->buffer[24] = (uint8_t)13;
	// my_struct->buffer[25] = (uint8_t)10;
}

void
decodeBuffer(uint8_t *arr, struct ROM_COMMUNICATION *my_struct, struct e1234567_status *e123)
{
	my_struct->right_actual_rpm = arr[0] + ( arr[1] << 8 );

	my_struct->left_actual_rpm = arr[2] + ( arr[3] << 8 );

	my_struct->right_encoder_count = arr[4] + ( arr[5]<<8) + (arr[6]<<16) + (arr[7]<<24);

	my_struct->left_encoder_count = arr[8] + ( arr[9]<<8) + (arr[10]<<16) + (arr[11]<<24);

	//my_struct->right_desire_rpm = arr[12] + ( arr[13] << 8 );
	//my_struct->left_desire_rpm = arr[14] + ( arr[15] << 8 );

	my_struct->free = arr[16];

//	uint8_t tmp = arr[17];
//	e123->estop_status = ( (int8_t)tmp & 0b10000000) >> 7;
//	e123->led1_status  = ( (int8_t)tmp & 0b01000000) >> 6;
//	e123->led2_status  = ( (int8_t)tmp & 0b00100000) >> 5;
//	e123->led3_status  = ( (int8_t)tmp & 0b00010000) >> 4;
//	e123->led4_status  = ( (int8_t)tmp & 0b00001000) >> 3;
//	e123->led5_status  = ( (int8_t)tmp & 0b00000100) >> 2;
//	e123->led6_status  = ( (int8_t)tmp & 0b00000010) >> 1;
//	e123->led7_status  = ( (int8_t)tmp & 0b00000001);

	my_struct->e1234567 = arr[17];

	my_struct->volt = arr[18];

	uint8_t tmp[4] = {arr[19], arr[20], arr[21], arr[22] };
	// byte array to float
	memcpy(&my_struct->ampere, tmp, 4);

	my_struct->checksum = arr[23];

	/* CHECKSUM CALCULATE */
		int32_t data[6]; //24bytes
		data[0] =  arr[0]+(arr[1] <<8)+(arr[2] <<16)+(arr[3] <<24);
		data[1] =  arr[4]+(arr[5] <<8)+(arr[6] <<16)+(arr[7] <<24);
		data[2] =  arr[8]+(arr[9] <<8)+(arr[10]<<16)+(arr[11]<<24);
		data[3] = arr[12]+(arr[13]<<8)+(arr[14]<<16)+(arr[15]<<24);
		data[4] = arr[16]+(arr[17]<<8)+(arr[18]<<16)+(arr[19]<<24);
		data[5] = arr[20]+(arr[21]<<8)+(arr[22]<<16)+(0x0000 <<24);

		my_struct->calculated_checksum = ROM_checksum(data);
}
#endif
void led_1_on(struct e1234567_status * my_struct)  { my_struct->led1_status=1; };
void led_1_off(struct e1234567_status * my_struct) { my_struct->led1_status=0; };

void led_2_on(struct e1234567_status * my_struct)  { my_struct->led2_status=1; };
void led_2_off(struct e1234567_status * my_struct) { my_struct->led2_status=0; };

void led_3_on(struct e1234567_status * my_struct)  { my_struct->led3_status=1; };
void led_3_off(struct e1234567_status * my_struct) { my_struct->led3_status=0; };

void led_4_on(struct e1234567_status * my_struct)  { my_struct->led4_status=1; };
void led_4_off(struct e1234567_status * my_struct) { my_struct->led4_status=0; };

void estop_on(struct e1234567_status * my_struct)  { my_struct->estop_status=1; };
void estop_off(struct e1234567_status * my_struct) { my_struct->led4_status =0; };

#endif /* APPLICATION_USER_CORE_ROM_COMMUNICATION_H_ */
