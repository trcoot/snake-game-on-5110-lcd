#include "lcd_5110_driver.h"

#define MAP_ROWS 6
#define MAP_COLS 10

Lcd_5110_Display::Lcd_5110_Display(int clkpin, int dinpin, int dcpin, int cepin,
								   int rstpin)
	: clkpin(clkpin), dinpin(dinpin), dcpin(dcpin), cepin(cepin),
	  rstpin(rstpin) {}

void Lcd_5110_Display::writeByte(volatile bool dc, volatile byte data) {
	digitalWrite(dcpin, dc);
	shiftOut(dinpin, clkpin, MSBFIRST, data);
}

void Lcd_5110_Display::initDisplay() {
	// initialize the pin
	pinMode(clkpin, OUTPUT);
	pinMode(dinpin, OUTPUT);
	pinMode(dcpin, OUTPUT);
	pinMode(cepin, OUTPUT);
	pinMode(rstpin, OUTPUT);

	// reset the display
	digitalWrite(rstpin, LOW);
	delay(1);
	digitalWrite(rstpin, HIGH);

	// the data for initialization
	// want more information? please refer to the document of PCD8544:
	// https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf
	writeByte(0, 0x21);
	writeByte(0, 0x06);
	writeByte(0, 0x13);
	writeByte(0, 0xc2);
	writeByte(0, 0x20);
	writeByte(0, 0x0c);

	// clear the display
	cleanDisplay();
}

void Lcd_5110_Display::showImg() {
	for (int i = 0; i < 504; i++) {
		writeByte(1, pgm_read_byte(welcome_img + i));
	}
}

void Lcd_5110_Display::drawDummy() {
	// draw 4*8 empty pixel
	writeByte(1, 0x00);
	writeByte(1, 0x00);
	writeByte(1, 0x00);
	writeByte(1, 0x00);
}

void Lcd_5110_Display::printBlock(int mark) {
	for (int i = 0; i < 8; i++)
		writeByte(1, pgm_read_byte(game_bitmap + mark * 8 + i));
}

void Lcd_5110_Display::cleanDisplay() {
	for (int i = 0; i < 504; i++)
		writeByte(1, 0x00);
}