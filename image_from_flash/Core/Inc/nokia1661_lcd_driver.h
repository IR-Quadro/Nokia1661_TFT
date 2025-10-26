/*
 * nokia1616/1661 TFT lcd Driver for AVR microcontroller
 * Copyright (C) 2018 mohammad mazarei (mohammad.mazarei [at] gmail.com)
 * web site: https://sisoog.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NOKIA1616_H
#define _NOKIA1616_H
#include <nokia1661_Hw.h>


struct font_header
{
	uint8_t header_offset;
	uint8_t char_offset;
	uint8_t width;
	uint8_t height;
	uint8_t h_spacing;
	uint8_t v_spacing;
	uint8_t number;
};

struct N1616Data
{
	uint16_t			bg_color;
	const uint8_t*		font_data;
	struct font_header	font_desc;
	uint8_t				charx;
	uint8_t				chary;
	uint8_t				charw;
	uint8_t				charh;
	uint8_t				orientation;
} ;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constants & types definition

#define LCD_CTRL_WIDTH		130
#define LCD_CTRL_HEIGHT		161
#define LCD_CTRL_X_OFFSET	1
#define LCD_CTRL_Y_OFFSET	1

typedef uint16_t rgb_color16bit;


// repack from 16bit presentation into color structure
#define rgb_color_repack(color)			(rgb_color16bit)color

#define DISPLAY_BGR_MODE

#ifdef DISPLAY_BGR_MODE
	// --- Settings for the new display (BGR format) ---
	// We change the color packing macro to swap Red and Blue
	#define rgb_color_pack(r, g, b)			((rgb_color16bit)b << 11) | ((rgb_color16bit)g << 5) | ((rgb_color16bit)r)

	// We also define the constant color values corresponding to the new format
	#define LCD_VGA_BLACK		rgb_color_repack(0x0000)
	#define LCD_VGA_WHITE		rgb_color_repack(0xFFFF)
	#define LCD_VGA_RED			rgb_color_repack(0x001F) // Value 0xF800 is for Blue
	#define LCD_VGA_GREEN		rgb_color_repack(0x1FE0) // Green unchanged
	#define LCD_VGA_BLUE		rgb_color_repack(0xF800) // Value 0x001F is for Red
	#define LCD_VGA_SILVER		rgb_color_repack(0xC618) // Calculated
	#define LCD_VGA_GRAY		rgb_color_repack(0x8410) // Calculated
	#define LCD_VGA_MAROON		rgb_color_repack(0x0010) // Actually NAVY
	#define LCD_VGA_YELLOW		rgb_color_repack(0x07FF) // Actually AQUA
	#define LCD_VGA_OLIVE		rgb_color_repack(0x0410) // Actually TEAL
	#define LCD_VGA_LIME		rgb_color_repack(0x07E0) // Green (other one) unchanged
	#define LCD_VGA_AQUA		rgb_color_repack(0xFFE0) // Actually YELLOW
	#define LCD_VGA_TEAL		rgb_color_repack(0x8400) // Actually OLIVE
	#define LCD_VGA_NAVY		rgb_color_repack(0x8000) // Actually MAROON
	#define LCD_VGA_FUCHSIA		rgb_color_repack(0xF81F) // Unchanged (since it has both Red and Blue)
	#define LCD_VGA_PURPLE		rgb_color_repack(0x8010) // Unchanged (since it has both Red and Blue)

#else
	// --- Settings for the old display (RGB format) - Your original code ---
	#define rgb_color_pack(r, g, b)			((rgb_color16bit)r << 11) | ((rgb_color16bit)g << 5) | ((rgb_color16bit)b)

	#define LCD_VGA_BLACK		rgb_color_repack(0x0000)
	#define LCD_VGA_WHITE		rgb_color_repack(0xFFFF)
	#define LCD_VGA_RED			rgb_color_repack(0xF800)
	#define LCD_VGA_GREEN		rgb_color_repack(0x1FE0)
	#define LCD_VGA_BLUE		rgb_color_repack(0x001F)
	#define LCD_VGA_SILVER		rgb_color_repack(0xC618)
	#define LCD_VGA_GRAY		rgb_color_repack(0x8410)
	#define LCD_VGA_MAROON		rgb_color_repack(0x8000)
	#define LCD_VGA_YELLOW		rgb_color_repack(0xFFE0)
	#define LCD_VGA_OLIVE		rgb_color_repack(0x8400)
	#define LCD_VGA_LIME		rgb_color_repack(0x07E0)
	#define LCD_VGA_AQUA		rgb_color_repack(0x07FF)
	#define LCD_VGA_TEAL		rgb_color_repack(0x0410)
	#define LCD_VGA_NAVY		rgb_color_repack(0x0010)
	#define LCD_VGA_FUCHSIA		rgb_color_repack(0xF81F)
	#define LCD_VGA_PURPLE		rgb_color_repack(0x8010)

#endif

// Note: The following macros in your original code have a bug and have been fixed
// (used & instead of |)
#define rgb_color_red(color)			((color >> 11) & 0x1F)
#define rgb_color_green(color)			((color >> 5) & 0x3F)
#define rgb_color_blue(color)			(color & 0x1F)

// clock wise rotation
// normal is the default orientation of selected LCD
enum { LCD_ORIENTATION_NORMAL=0, LCD_ORIENTATION_90, LCD_ORIENTATION_180, LCD_ORIENTATION_270 };

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// user functions definition

/**
* Sends command to lcd
*
* @data command to be send
*/
void _nlcdSendCmd(uint8_t data);

/**
* Sends data to lcd
*
* @data data to be send
*/
void _nlcdSendData(uint8_t data);

void _nlcdRead(uint8_t Reg,uint8_t *Readbuffer,uint8_t NRead);
/**
* inittialize lcd
*/
void nlcdInit();

/**
* Clear display by specified color
*
* @color color to use for clear
*/
void nlcdClear();

/**
* Set Pixel in Custom Location by specified color
*/
void nlcdPixel(uint8_t x, uint8_t y,rgb_color16bit color);

/**
* CSetting background color
*
* @color background color to be set
*/
void nlcdSetBackgroundColor(rgb_color16bit color);

void nlcdGotoCharXY(uint8_t x, uint8_t y);

void nlcdCharXY(uint8_t x, uint8_t y, rgb_color16bit color, char c);

void nlcdChar(rgb_color16bit color, char c);

void nlcdString(rgb_color16bit color, const char* str);

void nlcdStringXY(char x, char y, rgb_color16bit color, const char* str);

void nlcdStringP(rgb_color16bit color, const char* str);

void nlcdStringXYP(char x, char y, rgb_color16bit color, const char* str);

void nlcdSetFont(const uint8_t* font);

char nlcdFontLastChar();

char nlcdFontFirstChar();

void nlcdSetOrientation(uint8_t or);

uint8_t nlcdGetWidth();
uint8_t nlcdGetHeight();


// Private LCD functions (used internally)
void _nlcdSetWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void _nlcdSendPixel(rgb_color16bit color);



#endif

