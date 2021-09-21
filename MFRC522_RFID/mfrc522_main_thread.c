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
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>   //usleep()
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
/* Driver configuration */
#include "ti_drivers_config.h"

#include "lcd16x02.h"
#include "mfrc522.h"

SPI_Params spiParams;
SPI_Handle spiHandle;
SPI_Transaction spiTransaction = {0};

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    uint8_t cardID[5];
    char buffer[5];
    /* Call driver init functions */
    GPIO_init();
    SPI_init();
    // Initialize the SPI params
    SPI_Params_init(&spiParams);
    spiParams.bitRate = 4000000;
    spiParams.dataSize = 8;
    spiParams.transferMode = SPI_MODE_BLOCKING;
    spiHandle = SPI_open(CONFIG_SPI_0, &spiParams);
    if (spiHandle == NULL) {
        while(1){}
    }

    LCD16x02_Init();
    LCD16x02_Clear();
    MFRC522_Init();
    LCD16x02_SetPosition(0, 4);
    LCD16x02_String("RF CARD ID");
    while(1){
        if (MFRC522_Check(cardID) == MI_OK) {
            sprintf(buffer, "%02x %02x %02x %02x %02x", cardID[0], cardID[1], cardID[2],cardID[3],cardID[4] );
            LCD16x02_SetPosition(1, 1);
            LCD16x02_String(buffer);
            sleep(1);
        }
    }

}
