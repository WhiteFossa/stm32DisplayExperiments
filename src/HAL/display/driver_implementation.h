/*
 * driver_implementation.h
 *
 *  Created on: 12 янв. 2018 г.
 *      Author: fossa
 */

#ifndef HAL_DISPLAY_DRIVER_IMPLEMENTATION_H_
#define HAL_DISPLAY_DRIVER_IMPLEMENTATION_H_

#include "driver_prototype.h"
#include "../hal.h"

/**
 *		Display pins		MCU pins
 *
 * 1	#CS1				PORT A1
 * 2	#CS2				PORT A2
 * 3	GND
 * 4	VCC
 * 5	Contrast adjust
 * 6	Data / #Command		PORT A3
 * 7	Read / #Write		GND
 * 8	Enable				PORT A4
 *
 * 9	DB0					PORT B0
 * ..	..
 * 16	DB7					PORT B7
 */

/**
 * Port A bits.
 */
#define DISP_CS1			1
#define DISP_CS2			2
#define DISP_DC				3
#define DISP_E				4

/**
 * Data bus value can be obtained by applying this mask to argument of SendToDisplay().
 */
#define DISP_DATA_MASK		0x00FF;

/**
 * Bits for SendToDisplay word.
 */

/**
 * Set this bit in SendToDisplay word to make request to left controller. If not set, request will go to right controller.
 */
#define STD_LEFT_CTRLR		8

/**
 * Set this bit in SendToDisplay word to send command to display. Command always are being sent to both controllers, ignoring STD_LEFT_CTRLR.
 */
#define STD_COMMAND			9

/**
 * Call this function to send data/command to display. Data/command is in [0-7] bits.
 */
void SendToDisplay(uint16_t data);

/**
 * Dumb delay (later will be smarter).
 */
void Delay();

#endif /* HAL_DISPLAY_DRIVER_IMPLEMENTATION_H_ */
