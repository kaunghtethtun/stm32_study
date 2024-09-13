#include <stm32f4xx.h>

int main(void)
{
		RCC->AHB1ENR |= 1<<3; 
	  GPIOD->MODER |= 1<<24;
		GPIOD->OSPEEDR |= 1<<24;
		
	
	while(1)
	{
		GPIOD->ODR |= 1<<12;
		for(int i = 0; i<1000000000; i++);
		GPIOD->ODR &= ~(1<<12);
		for(int i = 0; i<1000000000; i++);
	}
}
