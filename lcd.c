


#include <avr/io.h>
#include <util/delay.h>

#include "logo_load.h"

#define DATA_PORT PORTB
#define DATA_DDR  DDRB

#define RS_PORT PORTD
#define RS_DDR  DDRD
#define RS_PIN PD0

#define RW_PORT PORTD
#define RW_DDR DDRD
#define RW_PIN PD1

#define EN_PORT PORTD
#define EN_DDR DDRD
#define EN_PIN PD2

#define CS1_PORT PORTD
#define CS1_DDR DDRD
#define CS1_PIN PD3

#define CS2_PORT PORTD
#define CS2_DDR DDRD
#define CS2_PIN PD4

#define RST_PORT PORTD
#define RST_DDR DDRD
#define RST_PIN PD5

#define HIGH(PORT,PIN) PORT |= (1<<PIN)
#define LOW(PORT,PIN) PORT &= ~(1<<PIN)
//#define HIGH(A) A##_PORT |= (1<<A##_PIN)
#define CHIP1 0x01
#define CHIP2 0x02


#define CMD_LCD_ON		0x3F
#define CMD_LCD_OFF		0x3E

#define CMD_LCD_SET_ADDRESS	0x40
#define CMD_LCD_SET_PAGE	0xB8
#define CMD_LCD_DISP_START	0xC0

#define PAGE0			0x00
#define ADDRESS0		0x00
#define LINE0			0x00

#define LCD_BUSY		0x80

void lcd_select_chip(uint8_t chip)
{
	switch(chip)
	{
	case CHIP1:
		HIGH(CS1_PORT, CS1_PIN);
		LOW(CS2_PORT, CS2_PIN);
		break;
	case CHIP2:
		LOW(CS1_PORT, CS1_PIN);
		HIGH(CS2_PORT, CS2_PIN);
		break;
	case (CHIP1|CHIP2):
		HIGH(CS1_PORT, CS1_PIN);
		HIGH(CS2_PORT, CS2_PIN);
		break;
	default:
		LOW(CS1_PORT, CS1_PIN);
		LOW(CS2_PORT, CS2_PIN);
		break;
	}
}

void lcd_write(uint8_t value, uint8_t chip)
{
	DATA_PORT = value;
	HIGH(EN_PORT, EN_PIN);
	_delay_us(2); //>1000ns
	LOW(EN_PORT,EN_PIN);
	
	_delay_us(1);//TODO: busy flag prüfen
	DATA_PORT = 0x00;
}

void lcd_cmd_write(uint8_t cmd, uint8_t chip)
{
	lcd_select_chip(chip);
	LOW(RW_PORT, RW_PIN);//write
	LOW(RS_PORT, RS_PIN);//instruction
	lcd_write(cmd, chip);

}

void lcd_data_write(uint8_t data, uint8_t chip)
{
	lcd_select_chip(chip);
	LOW(RW_PORT, RW_PIN);//write
	HIGH(RS_PORT, RS_PIN);//data
	lcd_write(data, chip);
}
void lcd_setup()
{
	RS_DDR |= (1<<RS_PIN);
	RW_DDR |= (1<<RW_PIN);
	EN_DDR |= (1<<EN_PIN);
	CS1_DDR |= (1<<CS1_PIN);
	CS2_DDR |= (1<<CS2_PIN);
	RST_DDR |= (1<<RST_PIN);
	DATA_DDR = 0xff;
}

void lcd_init()
{
	lcd_select_chip(CHIP1|CHIP2);

	LOW(RST_PORT,RST_PIN);//reset
	_delay_ms(30);
	HIGH(RST_PORT,RST_PIN);


	lcd_cmd_write(CMD_LCD_ON,CHIP1|CHIP2);
	lcd_cmd_write(CMD_LCD_DISP_START|LINE0,CHIP1|CHIP2);
	lcd_cmd_write(CMD_LCD_SET_ADDRESS|ADDRESS0,CHIP1|CHIP2);
	lcd_cmd_write(CMD_LCD_SET_PAGE|PAGE0,CHIP1|CHIP2);
}

void lcd_clear()
{
	for(uint8_t y = 0; y < 8; y++)
	{
		lcd_cmd_write(CMD_LCD_SET_PAGE|y,CHIP1|CHIP2);
		lcd_cmd_write(CMD_LCD_SET_ADDRESS|ADDRESS0,CHIP1|CHIP2);
		for(uint8_t x = 0; x < 64; x++)
		{
			lcd_data_write(0x00,CHIP1|CHIP2);
		}
		lcd_cmd_write(CMD_LCD_SET_PAGE|PAGE0,CHIP1|CHIP2);
		lcd_cmd_write(CMD_LCD_SET_ADDRESS|ADDRESS0,CHIP1|CHIP2);
	}
}

void draw_bitmap_fullscreen()
{
	uint8_t chip;
	for(chip=1;chip<=2; chip++)
	{
		for(
		uint8_t page = y/8;
	}
	lcd_cmd_write(CMD
	for(uint8_t
}


int main()
{
	lcd_setup();
	lcd_init();
	lcd_clear();

	lcd_data_write(0xFF,CHIP1);
	while(1)
	{
		uint8_t t=0;
		t++;
	}

}
