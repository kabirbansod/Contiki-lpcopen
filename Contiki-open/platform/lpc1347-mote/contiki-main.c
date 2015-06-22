/*
 * Copyright (c) 2002, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the Contiki OS
 *
 */

/**
 * \ingroup platform
 *
 * \defgroup native_platform Native platform
 *
 * Platform running in the host (Windows or Linux) environment.
 *
 * Used mainly for development and debugging.
 * @{
 */


#include "dev/leds.h"
#include "sys/process.h"
#include "sys/procinit.h"
#include "etimer.h"
#include "sys/autostart.h"
#include "chip.h"                        /* LPC13Uxx definitions */
#include "gpio_13xx_1.h"
//#include "timer16.h"

//#define CORE_M3
unsigned int idle_count = 0;
const uint32_t OscRateIn = 12000000;
const uint32_t ExtRateIn = 0;
uint32_t SystemCoreClock = 72000000;

static void platform_init();

int main()
{
  platform_init();
  //printf("Initializing\n");


  //printf("Clock init done\n");

  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  //printf("Processes running\n");
  while(1) {
    do {
    } while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */
  }
  return 0;
}

static void platform_init() {
	// ------------- USB -------------- //
/*	USBD_Init(&USB_OTG_dev,
	          USB_OTG_FS_CORE_ID,
	          &USR_desc,
	          &USBD_CDC_cb,
	          &USR_cb); */

	/*
	 * Disable STDOUT buffering. Otherwise nothing will be printed
	 * before a newline character or when the buffer is flushed.
	 */
	//setbuf(stdout, NULL);
	Chip_GPIO_Init(LPC_GPIO_PORT);
	clock_init();
	process_init();
	leds_init();

//#if WITH_UIP
//	slip_arch_init(115200);
//#endif /* WITH_UIP */

	//rtimer_init();
}
