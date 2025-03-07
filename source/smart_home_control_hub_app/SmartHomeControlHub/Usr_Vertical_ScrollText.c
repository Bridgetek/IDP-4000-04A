#include "Ft_Esd.h"
#include "Usr_Vertical_ScrollText.h"

int y = 0;
bool flagChange = false;
ESD_METHOD(Usr_Vertical_ScrollText_Render_Signal, Context = Usr_Vertical_ScrollText)
void Usr_Vertical_ScrollText_Render_Signal(Usr_Vertical_ScrollText *context)
{
	// ...
	
	void *owner = context->Owner;
	int gX = context->Widget.GlobalX;
	int gY = context->Widget.GlobalY;
	EVE_HalContext *phost = Esd_GetHost();
	EVE_CoCmd_dl(phost, SAVE_CONTEXT());
	Ft_Esd_Rect16 scissor = {
		.X = gX, .Y = gY, .Width = context->Widget.GlobalWidth, .Height = context->capsHeight + 4
	};
	scissor = Ft_Esd_Rect16_Crop(scissor, Ft_Esd_Dl_Scissor_Get());
	EVE_CoCmd_dl(phost, SCISSOR_XY(scissor.X, scissor.Y));
	EVE_CoCmd_dl(phost, SCISSOR_SIZE(scissor.Width, scissor.Height));
	int nextY, currentY;
	if(flagChange)
	{
	
		//printf("Change %d %d %d %d\n", context->Value, context->currentValue, context->nextValue, y);
		//bottom to top
		if(context->currentValue < context->nextValue)
		{
			currentY = (y < context->capsHeight) ? (context->capsHeight - y - 2) : (-context->capsHeight - 2);
			nextY = (y < context->capsHeight) ? -y - 2: 2;
		}
		else
		{
			//top to bottom
			currentY = (y < context->capsHeight) ? (y - context->capsHeight - 2) : (-context->capsHeight - 2);
			nextY = (y < context->capsHeight) ? y + 2: 2;
		}
	}
	else
	{
		//printf("%d %d %d %d\n", context->Value, context->currentValue, context->nextValue, y);
		//top to bottom
		if(context->currentValue < context->nextValue)
		{
			currentY = (y < context->capsHeight) ? y + 2 : 2;
			nextY = (y < context->capsHeight) ? ( y - context->capsHeight - 2): (-context->capsHeight - 2);
		}
		else
		{
			//bottom to top
			currentY = (y < context->capsHeight) ? -y - 2: 2;
			nextY = (y < context->capsHeight) ? (context->capsHeight - y - 2) : (-context->capsHeight - 2);
		}
	}
	
	int nextVal = context->nextValue;
	char nextCharArr[3] = {NULL, NULL, NULL}; 
    nextCharArr[1] =  nextVal % 10 + 48;
    nextVal /= 10;
    nextCharArr[0] = nextVal % 10 + 48;
	
	int currentVal = context->currentValue;
	char currentCharArr[3] = {NULL, NULL, NULL}; 
    currentCharArr[1] =  currentVal % 10 + 48;
    currentVal /= 10;
    currentCharArr[0] = currentVal % 10 + 48;
	
	Ft_Esd_Theme * theme = context->Theme(owner);
	ft_argb32_t c_1 = Ft_Esd_Theme_GetTextColor(theme);
	Ft_Esd_Dl_COLOR_RGB(c_1);
	
	if(y == 0 || y == context->capsHeight - 1)
	{
		if(flagChange)
		{
			EVE_CoCmd_text_ex(phost, gX + gX / 2, gY + 2, context->myFont, OPT_CENTERX, 0, context->baseLine, context->capsHeight, context->xOffset, context->nextValue == 0 ? "OFF" : nextCharArr);
		}
		else
		{
			EVE_CoCmd_text_ex(phost, gX + gX / 2, gY + 2, context->myFont, OPT_CENTERX, 0, context->baseLine, context->capsHeight, context->xOffset, context->currentValue == 0 ? "OFF" : currentCharArr);
			
		}
	}
	else
	{
		EVE_CoCmd_text_ex(phost, gX + gX / 2, gY + nextY, context->myFont, OPT_CENTERX, 0, context->baseLine, context->capsHeight, context->xOffset, context->nextValue == 0 ? "OFF" : nextCharArr);
		
		EVE_CoCmd_text_ex(phost, gX + gX / 2, gY + currentY, context->myFont, OPT_CENTERX, 0, context->baseLine, context->capsHeight, context->xOffset, context->currentValue == 0 ? "OFF" : currentCharArr);
	}
	EVE_CoCmd_dl(phost, RESTORE_CONTEXT());
}

ESD_METHOD(Usr_Vertical_ScrollText_ESD_Timer_Fired, Context = Usr_Vertical_ScrollText)
void Usr_Vertical_ScrollText_ESD_Timer_Fired(Usr_Vertical_ScrollText *context)
{
	if(flagChange)
	{
		context->currentValue = context->Value;
	}
	else
	{
		context->nextValue = context->Value;
	}
	if(context->nextValue == context->currentValue)
	{
		return;
	}
		
	if(y < context->capsHeight)
	{
		y++;
		if(y == context->capsHeight - 1)
		{
			y = 0;
			flagChange = !flagChange;
		}
	}
}

ESD_METHOD(Usr_Vertical_ScrollText_Start_Signal, Context = Usr_Vertical_ScrollText)
void Usr_Vertical_ScrollText_Start_Signal(Usr_Vertical_ScrollText *context)
{
	context->nextValue = context->Value;
}
