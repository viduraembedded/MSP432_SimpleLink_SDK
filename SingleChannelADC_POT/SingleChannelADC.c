/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== blink.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>   //usleep()
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/ADC.h>

/* Display Driver Header files */
#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>

/* Driver configuration */
#include "ti_drivers_config.h"

uint16_t adcValue = 0;
uint8_t ledStatus = 0;
uint16_t adcThreshold = 800;


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    //uint32_t number = 0;

    /* Call driver init functions */
    GPIO_init();
    Display_init();
    ADC_init();

    // Initialize Display params
    Display_Params uartParams;
    Display_Handle  uartHandle;
    Display_Params_init(&uartParams);
    uartHandle = Display_open(Display_Type_UART, &uartParams);

    // ADC configuration
    ADC_Params  adcParams;
    ADC_Handle  adchandle;
    ADC_Params_init(&adcParams);
    adchandle = ADC_open(CONFIG_ADC_0, &adcParams);

    while(1){
        uint16_t result;

        result = ADC_convert(adchandle, &adcValue);
        if (result == ADC_STATUS_SUCCESS) {
            if (adcValue >= adcThreshold) {
                GPIO_write(CONFIG_GPIO_BLUE_LED, CONFIG_GPIO_LED_ON);
                ledStatus = 1;

            } else {
                GPIO_write(CONFIG_GPIO_BLUE_LED, CONFIG_GPIO_LED_OFF);
                ledStatus = 0;
            }
        }
        Display_print1(uartHandle, 0, 0, "ADC Value is = %d", adcValue);
        usleep(500000);
    }
    //return 0;
}
