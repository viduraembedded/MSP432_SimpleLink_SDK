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

/* Driver configuration */
#include "ti_drivers_config.h"
uint8_t buttonPressed = 0;

uint8_t segmentNumbers[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
uint8_t number = 0;

void GPIO_Callback_Button_S1(uint_least8_t index)
{
    if (index == CONFIG_GPIO_BUTTON_S1) {
        buttonPressed = 1;
    }
}
void SevenSegment_Update(uint8_t number)
{
    GPIO_write(CONFIG_GPIO_SEG_A, ((number >> 0) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_B, ((number >> 1) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_C, ((number >> 2) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_D, ((number >> 3) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_E, ((number >> 4) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_F, ((number >> 5) & 0x01));
    GPIO_write(CONFIG_GPIO_SEG_G, ((number >> 6) & 0x01));
}
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /* Call driver init functions */
    GPIO_init();
    GPIO_setCallback(CONFIG_GPIO_BUTTON_S1, GPIO_Callback_Button_S1);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_S1);

    while(1){
        if (buttonPressed == 1) {
            SevenSegment_Update(segmentNumbers[number]);
            number++;
            if (number > 9) {
               number = 0;
            }
            buttonPressed = 0;
        } else {
            SevenSegment_Update(segmentNumbers[number]);
        }
        sleep(1);
    }
    //return 0;
}
