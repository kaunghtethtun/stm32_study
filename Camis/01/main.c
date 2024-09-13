#include <stm32f4xx.h>

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODE12_0;
	GPIOD->OTYPER |= GPIO_OTYPER_OT12_Pos;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0;
	
		while(1)
		{
			GPIOD->ODR |= GPIO_ODR_OD12_Msk;
			for(int i = 0; i<10; i++);
			GPIOD->ODR &= ~(GPIO_ODR_OD12_Msk);
		}
}
