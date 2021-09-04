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
#include <ti/drivers/I2C.h>

/* Display Driver Header files */
#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>

/* Driver configuration */
#include "ti_drivers_config.h"

// I2C configuration
I2C_Params mpu6050Params;
I2C_Handle mpu6050Handle;
I2C_Transaction i2cTranscation = {0};

#define MPU6050_ADDRESS 0x68

void MPU6050_Reset();
void MPU6050_ReadData(int16_t accelerometer[3], int16_t gyro[3], int16_t *temp);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    int16_t accelerometer[3], gyro[3], temp;

    /* Call driver init functions */
    GPIO_init();
    Display_init();
    I2C_init();

    // Initialize Display params
    Display_Params uartParams;
    Display_Handle  uartHandle;
    Display_Params_init(&uartParams);
    uartHandle = Display_open(Display_Type_UART, &uartParams);

    I2C_Params_init(&mpu6050Params);
    mpu6050Params.bitRate = I2C_400kHz;
    mpu6050Handle = I2C_open(CONFIG_I2C_0, &mpu6050Params);

    MPU6050_Reset();

    while(1)
    {
        MPU6050_ReadData(accelerometer, gyro, &temp);
        Display_print3(uartHandle, 0, 0, "Accelerometer   X_OUT= %d   Y_OUT= %d   Z_OUT= %d\r\n",accelerometer[0], accelerometer[1], accelerometer[2]);
        Display_print3(uartHandle, 1, 0, "Gyro   X_OUT= %d   Y_OUT= %d   Z_OUT= %d\r\n",gyro[0], gyro[1], gyro[2]);
        Display_print1(uartHandle, 2, 0, "Temperature= %2f \r\n", (temp/340.0) + 36.53);

        usleep(500000);
    }
    //return 0;
}


void MPU6050_Reset()
{
    uint8_t writeData[] = {0x6B, 0x00};

    i2cTranscation.slaveAddress = MPU6050_ADDRESS;
    i2cTranscation.writeBuf = writeData;
    i2cTranscation.writeCount = 2;

    I2C_transfer(mpu6050Handle, &i2cTranscation);
}
void MPU6050_ReadData(int16_t accelerometer[3], int16_t gyro[3], int16_t *temp)
{
    uint8_t readData[6];
    uint8_t writeData;
    // reading the accelerometer data
    writeData = 0x3B;
    i2cTranscation.slaveAddress = MPU6050_ADDRESS;
    i2cTranscation.writeBuf = &writeData;
    i2cTranscation.writeCount = 1;
    i2cTranscation.readBuf = readData;
    i2cTranscation.readCount = 6;
    I2C_transfer(mpu6050Handle, &i2cTranscation);

    accelerometer[0] = ((readData[0] << 8) | readData[1]);
    accelerometer[1] = ((readData[2] << 8) | readData[3]);
    accelerometer[2] = ((readData[4] << 8) | readData[5]);

    //Gyro data
    writeData = 0x43;
    i2cTranscation.slaveAddress = MPU6050_ADDRESS;
    i2cTranscation.writeBuf = &writeData;
    i2cTranscation.writeCount = 1;
    i2cTranscation.readBuf = readData;
    i2cTranscation.readCount = 6;
    I2C_transfer(mpu6050Handle, &i2cTranscation);

    gyro[0] = ((readData[0] << 8) | readData[1]);
    gyro[1] = ((readData[2] << 8) | readData[3]);
    gyro[2] = ((readData[4] << 8) | readData[5]);

    // read the temperture data
    writeData = 0x41;
    i2cTranscation.slaveAddress = MPU6050_ADDRESS;
    i2cTranscation.writeBuf = &writeData;
    i2cTranscation.writeCount = 1;
    i2cTranscation.readBuf = readData;
    i2cTranscation.readCount = 2;
    I2C_transfer(mpu6050Handle, &i2cTranscation);

    *temp = ((readData[0] << 8) | readData[1]);

}
