#ifndef SWTFT_Buttons_h
#define SWTFT_Buttons_h

#if defined(__AVR__)
	#include "Arduino.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
#elif defined(__arm__)
	#include "Arduino.h"
#endif

#define	VGA_BLACK   0x0000
#define	VGA_BLUE    0x001F
#define	VGA_RED     0xF800
#define	VGA_GREEN   0x07E0
#define VGA_CYAN    0x07FF
#define VGA_MAGENTA 0xF81F
#define VGA_YELLOW  0xFFE0
#define VGA_GRAY    0x7BEF
#define VGA_WHITE   0xFFFF

#include <SWTFT.h>
#include <SWTouch.h>

#define MAX_BUTTONS	10	// Maximum number of buttons available at one time

// Define presets for button status
#define BUTTON_DISABLED			  0x0001
#define BUTTON_SYMBOL			    0x0002
#define BUTTON_SYMBOL_REP_3X	0x0004
#define BUTTON_BITMAP			    0x0008	
#define BUTTON_NO_BORDER		  0x0010
#define BUTTON_UNUSED			    0x8000

typedef struct
{
  uint16_t			pos_x, pos_y, width, height;
  uint16_t			flags;
  char				*label;
  //bitmapdatatype	data;
} button_type;

class SWTFT_Buttons
{
	public:
		SWTFT_Buttons(SWTFT *ptrSWTFT, SWTouch *ptrSWTouch);

		int		addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *label, uint16_t flags=0);
		//int		addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, uint16_t flags=0);
		void	drawButtons();
		void	drawButton(int buttonID);
		void	enableButton(int buttonID, boolean redraw=false);
		void	disableButton(int buttonID, boolean redraw=false);
		void	relabelButton(int buttonID, char *label, boolean redraw=false);
		boolean	buttonEnabled(int buttonID);
		void	deleteButton(int buttonID);
		void	deleteAllButtons();
		int		checkButtons();
		void	setTextFont(uint8_t* font);
		void	setSymbolFont(uint8_t* font);
		void	setButtonColors(word atxt, word iatxt, word brd, word brdhi, word back);

	protected:
		SWTFT		*_SWTFT;
		SWTouch		*_SWTouch;
		button_type	buttons[MAX_BUTTONS];
		uint16_t		_color_text, _color_text_inactive, _color_background, _color_border, _color_hilite;
		uint8_t		*_font_text, *_font_symbol;
};

#endif
