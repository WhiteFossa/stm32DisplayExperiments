/*
 * driver.c
 *
 *  Created on: 12 янв. 2018 г.
 *      Author: fossa
 */

#include "driver_implementation.h"

void InitializeDisplay()
{
	// Clocking up ports A and B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

	// Full speed for needed pins
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1 | GPIO_OSPEEDER_OSPEEDR1_0
					| GPIO_OSPEEDER_OSPEEDR2_1 | GPIO_OSPEEDER_OSPEEDR2_0
					| GPIO_OSPEEDER_OSPEEDR3_1 | GPIO_OSPEEDER_OSPEEDR3_0
					| GPIO_OSPEEDER_OSPEEDR4_1 | GPIO_OSPEEDER_OSPEEDR4_0;

	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1 | GPIO_OSPEEDER_OSPEEDR0_0
					| GPIO_OSPEEDER_OSPEEDR1_1 | GPIO_OSPEEDER_OSPEEDR1_0
					| GPIO_OSPEEDER_OSPEEDR2_1 | GPIO_OSPEEDER_OSPEEDR2_0
					| GPIO_OSPEEDER_OSPEEDR3_1 | GPIO_OSPEEDER_OSPEEDR3_0
					| GPIO_OSPEEDER_OSPEEDR4_1 | GPIO_OSPEEDER_OSPEEDR4_0
					| GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR5_0
					| GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR6_0
					| GPIO_OSPEEDER_OSPEEDR7_1 | GPIO_OSPEEDER_OSPEEDR7_0;

	// Output mode for required pins
	// Masking our pins
	GPIOA->MODER &= ~(GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1
					| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER2_1
					| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER3_1
					| GPIO_MODER_MODER4_0 | GPIO_MODER_MODER4_1);
	// Setting
	GPIOA->MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
					| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0;

	GPIOB->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1
					| GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1
					| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER2_1
					| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER3_1
					| GPIO_MODER_MODER4_0 | GPIO_MODER_MODER4_1
					| GPIO_MODER_MODER5_0 | GPIO_MODER_MODER5_1
					| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER6_1
					| GPIO_MODER_MODER7_0 | GPIO_MODER_MODER7_1);

	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0
						| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0
						| GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0
						| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

	// Switching display on
	SendToDisplay(0b00111111 | (1 << STD_COMMAND));
}

void Delay()
{
	volatile uint32_t timer = 0x3FFF;
	while (timer--);
}

void SendToDisplay(uint16_t data)
{
	GPIOB->ODR = data & DISP_DATA_MASK;

	// Both controllers off
	uint16_t toPort = (1 << DISP_CS1) | (1 << DISP_CS2);

	if ((data & (1 << STD_COMMAND)) != 0)
	{
		// Command, writing to both controllers
		toPort &= ~((1 << DISP_CS1) | (1 << DISP_CS2));
	}
	else
	{
		// Data
		toPort |= (1 << DISP_DC);

		// To what controller?
		if ((data & (1 << STD_LEFT_CTRLR)) != 0)
		{
			toPort &= ~(1 << DISP_CS1);
		}
		else
		{
			toPort &= ~(1 << DISP_CS2);
		}
	}

	GPIOA->ODR = toPort;

	Delay();

	toPort |= (1 << DISP_E);
	GPIOA->ODR = toPort;

	Delay();

	toPort &= ~(1 << DISP_E);
	toPort |= (1 << DISP_CS1) | (1 << DISP_CS2);
	GPIOA->ODR = toPort;

	Delay();
}


