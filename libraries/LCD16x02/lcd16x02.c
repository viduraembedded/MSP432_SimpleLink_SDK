/*
 * lcd16x02.c
 *
 *  Created on: 12-Sep-2021
 *      Author: Vidura Embedded
 */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>   //usleep()
/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#include "lcd16x02.h"

#define RS_HIGH()    GPIO_write(CONFIG_GPIO_RS_PIN, 1)
#define RS_LOW()     GPIO_write(CONFIG_GPIO_RS_PIN, 0)
#define EN_HIGH()    GPIO_write(CONFIG_GPIO_EN_PIN, 1)
#define EN_LOW()     GPIO_write(CONFIG_GPIO_EN_PIN, 0)


void LCD16x02_Init(void)
{

    usleep(50000);
    LCD16x02_Command(0x30);
    usleep(5000);
    LCD16x02_Command(0x30);
    usleep(1000);
    LCD16x02_Command(0x30);
    usleep(10000);
    LCD16x02_Command(0x20);
    usleep(10000);

    LCD16x02_Command(0x28);
    usleep(1000);
    LCD16x02_Command(0x08);
    usleep(1000);
    LCD16x02_Command(0x01);
    usleep(1000);
    LCD16x02_Command(0x06);
    usleep(1000);
    LCD16x02_Command(0x0C);
}

void LCD16x02_Command(char cmd)
{
    char lcdData;
    lcdData = (cmd >> 4) & 0x0f;
    RS_LOW(); /*Command Register is selected i.e.RS=0*/
    GPIO_write(CONFIG_GPIO_D7_PIN, ((lcdData>>3)&0x01));
    GPIO_write(CONFIG_GPIO_D6_PIN, ((lcdData>>2)&0x01));
    GPIO_write(CONFIG_GPIO_D5_PIN, ((lcdData>>1)&0x01));
    GPIO_write(CONFIG_GPIO_D4_PIN, ((lcdData>>0)&0x01));  /*Send MSB nibble of command first*/
    EN_HIGH();  /*High-to-low pulse on Enable pin to latch data*/
    usleep(40);
    EN_LOW();
    usleep(40);
    lcdData = (cmd & 0x0F); /*Send lower nibble of command */
    GPIO_write(CONFIG_GPIO_D7_PIN, ((lcdData>>3)&0x01));
    GPIO_write(CONFIG_GPIO_D6_PIN, ((lcdData>>2)&0x01));
    GPIO_write(CONFIG_GPIO_D5_PIN, ((lcdData>>1)&0x01));
    GPIO_write(CONFIG_GPIO_D4_PIN, ((lcdData>>0)&0x01));
    EN_HIGH();  /*High-to-low pulse on Enable pin to latch data*/
    usleep(40);
    EN_LOW();
    usleep(40);
}

void LCD16x02_Char(char data)
{
    char lcdData;
    RS_HIGH(); /*Command Register is selected i.e.RS=1*/
    lcdData = (data >> 4) & 0x0F;  /*Send MSB nibble of command first*/
    GPIO_write(CONFIG_GPIO_D7_PIN, ((lcdData>>3)&0x01));
    GPIO_write(CONFIG_GPIO_D6_PIN, ((lcdData>>2)&0x01));
    GPIO_write(CONFIG_GPIO_D5_PIN, ((lcdData>>1)&0x01));
    GPIO_write(CONFIG_GPIO_D4_PIN, ((lcdData>>0)&0x01));

    EN_HIGH();  /*High-to-low pulse on Enable pin to latch data*/
    usleep(40);
    EN_LOW();
    usleep(40);
    lcdData = (data&0x0F); /*Send lower nibble of command */
    GPIO_write(CONFIG_GPIO_D7_PIN, ((lcdData>>3)&0x01));
    GPIO_write(CONFIG_GPIO_D6_PIN, ((lcdData>>2)&0x01));
    GPIO_write(CONFIG_GPIO_D5_PIN, ((lcdData>>1)&0x01));
    GPIO_write(CONFIG_GPIO_D4_PIN, ((lcdData>>0)&0x01));
    EN_HIGH();  /*High-to-low pulse on Enable pin to latch data*/
    usleep(40);
    EN_LOW();
    usleep(40);
}
void LCD16x02_Clear(void)
{
    LCD16x02_Command(0x01);  /*clear display screen*/
    sleep(1);
}
void LCD16x02_String(const char *message)
{
    while((*message)!=0)
    {
        LCD16x02_Char(*message);
        message++;
    }
}
void LCD16x02_SetPosition(char row, char col)
{
    switch (row) {
    case 0:
        col |= 0x80;
        break;
    case 1:
        col |= 0xC0;
        break;
    }
    LCD16x02_Command(col);
}
