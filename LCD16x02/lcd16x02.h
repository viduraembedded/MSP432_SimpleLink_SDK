/*
 * lcd16x02.h
 *
 *  Created on: 12-Sep-2021
 *      Author: Vidura Embedded
 */

#ifndef LCD16X02_H_
#define LCD16X02_H_

void LCD16x02_Init(void);
void LCD16x02_Clear(void);
void LCD16x02_Command(char cmd);
void LCD16x02_Char(char data);
void LCD16x02_String(const char *message);
void LCD16x02_SetPosition(char row, char col);

#endif /* LCD16X02_H_ */
