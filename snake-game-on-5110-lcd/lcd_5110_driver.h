/**========================================================================
 * ?                              ABOUT
 * @author         :  trcoot@github
 * @email          :  jojokagami@gmail.com
 * @description    :  the driver of LCD 5110
 *========================================================================**/

#include <Arduino.h>

const PROGMEM byte welcome_img[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40,
	0x80, 0x80, 0x40, 0x60, 0x10, 0x90, 0x98, 0x48, 0xC8, 0x90, 0x60, 0x40,
	0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0xFC, 0xFC, 0xFC, 0x00, 0x00,
	0x00, 0xFC, 0xFC, 0xFC, 0x00, 0xFC, 0xFC, 0xF8, 0xE0, 0xC0, 0x80, 0xF8,
	0xF8, 0xF8, 0x00, 0xE0, 0xF0, 0xF0, 0x78, 0x38, 0x78, 0xF8, 0xF0, 0xC0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x40, 0xC0, 0x60, 0xA0, 0x70, 0xB0, 0x58, 0xA8, 0x58, 0xAC, 0x54, 0xAC,
	0x54, 0xAC, 0xD4, 0xAC, 0xD4, 0x7C, 0x48, 0x48, 0x4F, 0x49, 0x45, 0x47,
	0x40, 0x40, 0x88, 0x04, 0x07, 0x04, 0x84, 0x86, 0x87, 0x83, 0x88, 0xC8,
	0xF8, 0xC8, 0xC8, 0xC0, 0x43, 0xDC, 0x70, 0xC7, 0x5F, 0xDF, 0x5C, 0x98,
	0x1C, 0x3F, 0x3F, 0x3F, 0x00, 0x3F, 0x3F, 0x3F, 0x03, 0x07, 0x0F, 0x3F,
	0x7F, 0x7F, 0x00, 0x1F, 0x3F, 0x7F, 0x78, 0x70, 0x78, 0x3F, 0x1F, 0x0F,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xD8, 0xAC, 0x57, 0xAA,
	0x55, 0xEA, 0xD5, 0xFA, 0x1D, 0x06, 0x07, 0x06, 0x03, 0x02, 0x03, 0x01,
	0x01, 0x01, 0x00, 0x00, 0x03, 0x1E, 0x22, 0x3C, 0x0C, 0x8C, 0xFC, 0xFC,
	0x9C, 0x0C, 0x9D, 0x62, 0x3E, 0x0F, 0x07, 0x03, 0xC1, 0xE1, 0x31, 0x1F,
	0x01, 0x03, 0xC3, 0x22, 0x1D, 0x0A, 0x0D, 0x8A, 0x8D, 0x8A, 0x8D, 0x8A,
	0x8D, 0x8A, 0x8C, 0x88, 0x88, 0x08, 0x08, 0x10, 0x60, 0xC0, 0xC0, 0xC0,
	0xE0, 0xD0, 0x10, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xC0, 0xBC, 0x5A, 0xB6, 0x5A, 0xB7, 0xEB, 0xD5, 0xAB, 0x7D,
	0xEB, 0x4D, 0xEA, 0x7D, 0xFB, 0x75, 0xAB, 0x77, 0xAB, 0x7E, 0xB0, 0x60,
	0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x41, 0x20, 0x10, 0x08,
	0x07, 0x81, 0xE0, 0x70, 0x38, 0x9C, 0x8E, 0x87, 0x01, 0xC0, 0x38, 0x06,
	0x01, 0x01, 0xC0, 0x30, 0x08, 0x06, 0xC1, 0xF0, 0x70, 0x90, 0x18, 0x38,
	0x68, 0x68, 0x78, 0x78, 0x70, 0x79, 0x6E, 0x60, 0x60, 0x60, 0x1F, 0x3F,
	0x7C, 0x9F, 0x7F, 0xFE, 0xF0, 0x80, 0x80, 0x03, 0x1C, 0xE8, 0x70, 0x00,
	0x00, 0x00, 0xC1, 0xC2, 0xE3, 0xE2, 0xE3, 0xE2, 0xE3, 0xE7, 0xC6, 0xCF,
	0xDE, 0x1D, 0x1A, 0xF5, 0x1A, 0xF5, 0x7B, 0x75, 0x7B, 0xF5, 0x7B, 0xF5,
	0x3B, 0xF5, 0x3B, 0x1E, 0xC0, 0x3C, 0x03, 0x00, 0x00, 0x00, 0x60, 0x9C,
	0x07, 0x23, 0x38, 0x7C, 0x7F, 0x7F, 0x7F, 0xFF, 0xFC, 0x63, 0x44, 0x18,
	0x20, 0x20, 0xC0, 0x83, 0x04, 0x18, 0x23, 0x47, 0xCF, 0x18, 0x27, 0xC4,
	0xC4, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x44, 0x44, 0xC4, 0xC4,
	0x5B, 0xB4, 0xFF, 0x3F, 0x7F, 0xFF, 0xEC, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0x03, 0x0F, 0x1F, 0x1F, 0x1F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
	0x7F, 0x7F, 0xFC, 0xFD, 0xFD, 0xF0, 0xF0, 0xF0, 0xF2, 0xF1, 0xF2, 0xF1,
	0xF1, 0xF0, 0xF0, 0xF0, 0xE3, 0x8C, 0x98, 0x10, 0x30, 0x60, 0x40, 0x41,
	0x81, 0x81, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
	0x82, 0x82, 0x82, 0x41, 0x40, 0x40, 0x60, 0x10, 0x19, 0x8F, 0xE0, 0xEF,
	0x8C, 0x9D, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x8C, 0xEC, 0xED, 0xED,
	0x62, 0x73, 0x31, 0x32, 0x32, 0x33, 0x33, 0x32, 0x12, 0x11, 0x0C, 0x00};

const PROGMEM byte game_bitmap[] = {
	// body_up
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
	// body_left
	0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
	// body_down
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
	// body_right
	0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
	// body_left_up and body_down_right
	0x00, 0x00, 0x03, 0x0f, 0x1f, 0x1f, 0x3e, 0x3c,
	// body_up_left and body_right_down
	0x3c, 0x7c, 0xf8, 0xf8, 0xf0, 0xc0, 0x00, 0x00,
	// body_left_down and up_right
	0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0x7c, 0x3c,
	// body_right_up and down_left
	0x3c, 0x3e, 0x1f, 0x1f, 0x0f, 0x03, 0x00, 0x00,
	// food
	0x00, 0x3c, 0x7e, 0x7e, 0x7e, 0x7a, 0x3c, 0x00,
	// empty
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	// tail(up)
	0x00, 0x00, 0x0f, 0x7f, 0x7f, 0x0f, 0x00, 0x00,
	// tail(left)
	0x3c, 0x3c, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x00,
	// tail(down)
	0x00, 0x00, 0xf0, 0xfe, 0xfe, 0xf0, 0x00, 0x00,
	// tail(right)
	0x00, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x3c,
	// head(up)
	0x00, 0x3c, 0xfa, 0xff, 0xff, 0xfa, 0x3c, 0x00,
	// head(left)
	0x18, 0x3c, 0x5a, 0x7e, 0x7e, 0x7e, 0x3c, 0x3c,
	// head(down)
	0x00, 0x3c, 0x5f, 0xff, 0xff, 0x5f, 0x3c, 0x00,
	// head(right)
	0x3c, 0x3c, 0x7e, 0x7e, 0x7e, 0x5a, 0x3c, 0x18};

class Lcd_5110_Display {
private:
	int clkpin, dinpin, dcpin, cepin, rstpin;
	void writeByte(bool, byte);

public:
	Lcd_5110_Display(int, int, int, int, int);
	void initDisplay();
	void showImg();
	void drawDummy();
	void printBlock(int);
	void cleanDisplay();
};