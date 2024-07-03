#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LCD_16x2_H_file.h"

#define RELAY_PIN   PC0   // Relay dihubungkan ke pin PC0

int val;
long R;
double Thermister;
int relay;

void ADC_Init()
{
	DDRA=0x00;      /* Mengubah Port ADC sebagai Input */
	ADCSRA = 0x87;      /* Enable ADC dan menentukan prescaler 128  */
}

int adc()
{
	ADMUX = 0x40;       /* Vref: Avcc, ADC channel: 0 */
	ADCSRA |= (1<<ADSC);    /* Memulai konversi ADC */
	while ((ADCSRA &(1<<ADIF))==0);    /* Menunggu sampai konversi ADC selesai  */
	ADCSRA |=(1<<ADIF);    /* Menyetel bit ADIF pada register ADCSRA */
	return(ADCW);      /* return ADCW */
}

double getTemp()
{
	val = adc();        /* Nilai ADC di berikan ke register val */
	R=((10230000/val) - 10000);/* Mneghitung nilai resistansi */
	Thermister = log(R);    /* Menghitung nilai Log dari resistansi */
	/* Persamaan Steinhart-Hart Thermistor: */
	/* nilai temperatur pada Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)        */
	/* A, B, C adalah koefisien, dimana A = 0.001129148, B = 0.000234125 dan C = 8.76741*10^-8  */
	Thermister = 1 / (0.001129148 + (0.000234125 * Thermister) + (0.0000000876741 * Thermister * Thermister * Thermister));
	Thermister = Thermister - 273.15;/* Mengubah dari satuan kelvin ke derajat °C */
	
	return Thermister;
}

void relay_init() {
	DDRD |= (1 << RELAY_PIN);   /* Atur pin relay sebagai output*/
}

void relay_off() {
	PORTD |= (1 << RELAY_PIN);  /* Nonaktifkan relay (input HIGH)*/
}

void relay_on() {
	PORTD &= ~(1 << RELAY_PIN); /* Aktifkan relay (input LOW)*/
}

int main(void)
{
	char array[20],ohm=0xF4;
	double temp;
	LCD_Init();     /* Inisialisasi 16x2 LCD */
	ADC_Init();     /* Inisialisasi ADC */
	relay_init();   /* Inisialisasi relay */
	LCD_Clear();    /* clear LCD */
	LCD_String_xy(1, 0,"Temp: ");
	LCD_String_xy(2, 0, "R: ");
	while(1)
	{
		temp = getTemp();/* Berikan nilai temperature ke temp */
		memset(array,0,20);
		dtostrf(temp,3,2,array);
		LCD_String_xy(1, 7,array);
		LCD_Char(0xDF); /* Nilai ASCII untuk derajat '°' */
		LCD_String("C   ");
		
		memset(array,0,20);
		sprintf(array,"%ld %c   ",R,ohm);
		LCD_String_xy(2, 3,array);
		
		/* Cek apakah suhu melebihi atau sama dengan 40 derajat Celsius */
		if(temp >= 40) {
			relay_off();    /* Aktifkan relay (input LOW) */
			} else {
			relay_on();   /* Nonaktifkan relay (input HIGH) */
		}
		

		_delay_ms(100);/* delay 0.1 detik */
	}
	
}
