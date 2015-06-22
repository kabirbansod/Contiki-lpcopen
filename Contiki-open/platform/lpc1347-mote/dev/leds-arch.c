/*
 * Author  : Benjamin Vedder
 * Created : 2013-05-31
 */

#include "contiki.h"
#include "dev/leds.h"
#include "chip.h"

//#define LEDS_PORT LPC_GPIO->MPIN[PORT1]

static int green_on = 0;
static int yellow_on = 0;
//static int red_on = 0;

void leds_arch_init(void) {
	//LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	Chip_GPIO_WriteDirBit(LPC_GPIO_PORT, 1, 13, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO_PORT, 1, 14, true);

}

unsigned char leds_arch_get(void) {
	return (green_on ? 0 : LEDS_GREEN)
		| (yellow_on ? 0 : LEDS_YELLOW);
}

void leds_arch_set(unsigned char leds) {
	if(leds & LEDS_GREEN) {
		Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 1, 13, false);
		green_on = 1;
	} else {
		Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 1, 13, true);
		green_on = 0;
	}

	if(leds & LEDS_YELLOW) {
		Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 1, 14, false);
		yellow_on = 1;
	} else {
		Chip_GPIO_WritePortBit(LPC_GPIO_PORT, 1, 14, true);
		yellow_on = 0;
	}

/*	if(leds & LEDS_RED) {
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		red_on = 1;
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		red_on = 0;
	}
*/
}

