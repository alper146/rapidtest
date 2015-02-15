#include "SWTFT_Buttons.h"
#include <Adafruit_GFX.h>
#include <SWTFT.h>
#include <SWTouch.h>

SWTFT_Buttons::SWTFT_Buttons(SWTFT *ptrSWTFT, SWTouch *ptrSWTouch)
{
	_SWTFT = ptrSWTFT;
	_SWTouch = ptrSWTouch;
	deleteAllButtons();
	_color_text				= VGA_WHITE;
	_color_text_inactive	= VGA_GRAY;
	_color_background		= VGA_BLUE;
	_color_border			= VGA_WHITE;
	_color_hilite			= VGA_RED;
	_font_text				= NULL;
	_font_symbol			= NULL;
}

int SWTFT_Buttons::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *label, uint16_t flags)
{
	int btcnt = 0;
  
	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) and (btcnt<MAX_BUTTONS))
		btcnt++;
  
	if (btcnt == MAX_BUTTONS)
		return -1;
	else
	{
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags;
		buttons[btcnt].label  = label;
//		buttons[btcnt].data   = NULL;
		return btcnt;
	}
}
/*
int SWTFT_Buttons::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, uint16_t flags)
{
	int btcnt = 0;
  
	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) and (btcnt<MAX_BUTTONS))
		btcnt++;
  
	if (btcnt == MAX_BUTTONS)
		return -1;
	else
	{
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags | BUTTON_BITMAP;
		buttons[btcnt].label  = NULL;
		buttons[btcnt].data   = data;
		return btcnt;
	}
}
*/

void SWTFT_Buttons::drawButtons()
{
	for (int i=0;i<MAX_BUTTONS;i++)
	{
		if ((buttons[i].flags & BUTTON_UNUSED) == 0)
			drawButton(i);
	}
}

void SWTFT_Buttons::drawButton(int buttonID)
{
	int		text_x, text_y;

	uint16_t	_current_color = _SWTFT->getColor();
	uint16_t	_current_back  = _SWTFT->getBGColor();
/*
	if (buttons[buttonID].flags & BUTTON_BITMAP)
	{
		_SWTFT->drawBitmap(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height, buttons[buttonID].data);
		if (!(buttons[buttonID].flags & BUTTON_NO_BORDER))
		{
			if ((buttons[buttonID].flags & BUTTON_DISABLED))
				_SWTFT->setColor(_color_text_inactive);
			else
				_SWTFT->setColor(_color_border);
			_SWTFT->drawRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
		}
	}
	else*/
	{
		_SWTFT->setColor(_color_background);
		_SWTFT->SW_fillRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height);
		_SWTFT->setColor(_color_border);
		_SWTFT->SW_drawRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height);
		if (buttons[buttonID].flags & BUTTON_DISABLED)
			_SWTFT->setColor(_color_text_inactive);
		else
			_SWTFT->setColor(_color_text);
    /*
		if (buttons[buttonID].flags & BUTTON_SYMBOL)
		{
			_SWTFT->setFont(_font_symbol);
			text_x = (buttons[buttonID].width/2) - (_SWTFT->getFontSize()/2) + buttons[buttonID].pos_x;
			text_y = (buttons[buttonID].height/2) - (_SWTFT->getFontSize()/2) + buttons[buttonID].pos_y;
		}
		else*/
		{
			text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * _SWTFT->getFontSize())/2)) + buttons[buttonID].pos_x;
			text_y = (buttons[buttonID].height/2) - (_SWTFT->getFontSize()/2) + buttons[buttonID].pos_y;
		}
    
		_SWTFT->setBGColor(_color_background);
		_SWTFT->drawText(buttons[buttonID].label, text_x, text_y);
		if ((buttons[buttonID].flags & BUTTON_SYMBOL) and (buttons[buttonID].flags & BUTTON_SYMBOL_REP_3X))
		{
			_SWTFT->drawText(buttons[buttonID].label, text_x-_SWTFT->getFontSize(), text_y);
			_SWTFT->drawText(buttons[buttonID].label, text_x+_SWTFT->getFontSize(), text_y);
		}
	}
	_SWTFT->setColor(_current_color);
	_SWTFT->setBGColor(_current_back);
}

void SWTFT_Buttons::enableButton(int buttonID, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags = buttons[buttonID].flags & ~BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

void SWTFT_Buttons::disableButton(int buttonID, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags = buttons[buttonID].flags | BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

void SWTFT_Buttons::relabelButton(int buttonID, char *label, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].label = label;
		if (redraw)
			drawButton(buttonID);
	}
}

boolean SWTFT_Buttons::buttonEnabled(int buttonID)
{
	return !(buttons[buttonID].flags & BUTTON_DISABLED);
}
    
void SWTFT_Buttons::deleteButton(int buttonID)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
		buttons[buttonID].flags = BUTTON_UNUSED;
}

void SWTFT_Buttons::deleteAllButtons()
{
	for (int i=0;i<MAX_BUTTONS;i++)
	{
		buttons[i].pos_x=0;
		buttons[i].pos_y=0;
		buttons[i].width=0;
		buttons[i].height=0;
		buttons[i].flags=BUTTON_UNUSED;
		buttons[i].label="";
	}
}

int SWTFT_Buttons::checkButtons()
{
  if (_SWTouch->touchAvailable() == true)
  {
		int		result = -1;
		int		touch_x = _SWTouch->getX();
		int		touch_y = _SWTouch->getY();
		word	_current_color = _SWTFT->getColor();
  
		for (int i=0;i<MAX_BUTTONS;i++)
		{
			if (((buttons[i].flags & BUTTON_UNUSED) == 0) and ((buttons[i].flags & BUTTON_DISABLED) == 0) and (result == -1))
			{
				if ((touch_x >= buttons[i].pos_x) and (touch_x <= (buttons[i].pos_x + buttons[i].width)) and (touch_y >= buttons[i].pos_y) and (touch_y <= (buttons[i].pos_y + buttons[i].height)))
					result = i;
			}
		}
		if (result != -1)
		{
			if (!(buttons[result].flags & BUTTON_NO_BORDER))
			{
				_SWTFT->setColor(_color_hilite);
        /*
				if (buttons[result].flags & BUTTON_BITMAP)
					_SWTFT->drawRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
				else*/
					_SWTFT->SW_drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].width, buttons[result].height);
			}
		}

		while (_SWTouch->touchAvailable() == true) {};

		if (result != -1)
		{
			if (!(buttons[result].flags & BUTTON_NO_BORDER))
			{
				_SWTFT->setColor(_color_border);
        /*
				if (buttons[result].flags & BUTTON_BITMAP)
					_SWTFT->drawRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
				else*/
					_SWTFT->SW_drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].width, buttons[result].height);
			}
		}

		_SWTFT->setColor(_current_color);
		return result;
	}
	else
		return -1;
}

void SWTFT_Buttons::setTextFont(uint8_t* font)
{
	_font_text = font;
}

void SWTFT_Buttons::setSymbolFont(uint8_t* font)
{
	_font_symbol = font;
}

void SWTFT_Buttons::setButtonColors(word atxt, word iatxt, word brd, word brdhi, word back)
{
	_color_text				= atxt;
	_color_text_inactive	= iatxt;
	_color_background		= back;
	_color_border			= brd;
	_color_hilite			= brdhi;
}
