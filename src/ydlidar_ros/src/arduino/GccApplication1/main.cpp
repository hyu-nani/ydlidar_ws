/*
 * GccApplication1.cpp
 *
 * Created: 2022-05-26 ?¤í›„ 2:24:17
 * Author : cube_
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x01;
	ADMUX = 0xAF;
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

