/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stm32f0xx.h>

int main(void)
{
	uint32_t SoS = 0b1010100111011101110010101;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	//uint8_t iter=0;
	while (1)
	{

		//GPIOA->BSRR = (1<<5); // set
		//GPIOA->BRR = (1<<5); // reset
		for(uint32_t j = 0; j < 32; j++)
		{
			if (SoS & (1<<j))
			{
				GPIOA->BSRR = (1<<5);
			}
			else
			{
				GPIOA->BRR = (1<<5);
			}

			for (volatile uint32_t i = 0; i < 100000; i++) {}
		}


	}


}
