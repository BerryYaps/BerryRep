/*
 *
 library LCD 16 X 2 menggunakan PORTB sebagai command port
 dan PORTD sebagai data port
 *
 */

#ifndef LCD_16x2_H_H_					/* Define library H file jika tidak didefinisikan */
#define LCD_16x2_H_H_

#define F_CPU 16000000UL				/* Define frekuensi CPU 16 Mhz*/
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include Delay header file */

#define LCD_Data_Dir DDRD			/* Define direksi register data LCD */
#define LCD_Command_Dir DDRB			/* Define direksi register command LCD */
#define LCD_Data_Port PORTD				/* Define port data LCD  */
#define LCD_Command_Port PORTB			/* Define port data LCD  */
#define EN PB0							/* Define pin Enable*/
#define RW PB1							/* Define pin Read/Write */
#define RS PB2	 						/* Define pin Register Select (data reg./command reg.) */

void LCD_Command (char);				/* Fungsi LCD command write */
void LCD_Char (char);					/* Fungsi LCD data write  */
void LCD_Init (void);					/* Fungsi LCD Initialize function */
void LCD_String (char*);				/* Fungsi untuk mengirimkan string ke LCD */
void LCD_String_xy (char,char,char*);	/* Fungsi untuk mengirimkan String pada baris dan kolom tertentu */
void LCD_Clear (void);					/* Fungsi LCD clear */


#endif									/* LCD_16x2_H_FILE_H_ */