/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_RSSIBar
C Source
*/

#include "Ft_Esd_RSSIBar.h"

#include "Esd_Context.h"
#include "Ft_Esd_Dl.h"

ESD_CORE_EXPORT void Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_RSSIBar_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_argb32_t Ft_Esd_RSSIBar_Default_Color__Default(void *context) { return 0xff969696UL; }
ft_argb32_t Ft_Esd_RSSIBar_Fill_Color__Default(void *context) { return 0xff0d36f0UL; }
int Ft_Esd_RSSIBar_Min_Strength__Default(void *context) { return 1L; }
int Ft_Esd_RSSIBar_Max_Strength__Default(void *context) { return 5L; }
int Ft_Esd_RSSIBar_Number_of_Bars__Default(void *context) { return 5L; }
int Ft_Esd_RSSIBar_Current_Strength__Default(void *context) { return 3L; }
ft_bool_t Ft_Esd_RSSIBar_Signal_Search_Mode__Default(void *context) { return 0; }


static Ft_Esd_WidgetSlots s_Ft_Esd_RSSIBar__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Widget_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_RSSIBar_Update,
	(void(*)(void *))Ft_Esd_RSSIBar_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Widget_End,
};


void Ft_Esd_RSSIBar__Initializer(Ft_Esd_RSSIBar *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_RSSIBar_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_RSSIBar__Slots;
	context->Widget.LocalX = 100;
	context->Widget.LocalY = 60;
	context->Widget.LocalWidth = 200;
	context->Widget.LocalHeight = 200;
	context->Theme = Ft_Esd_RSSIBar_Theme__Default;
	context->Default_Color = Ft_Esd_RSSIBar_Default_Color__Default;
	context->Fill_Color = Ft_Esd_RSSIBar_Fill_Color__Default;
	context->Min_Strength = Ft_Esd_RSSIBar_Min_Strength__Default;
	context->Max_Strength = Ft_Esd_RSSIBar_Max_Strength__Default;
	context->Number_of_Bars = Ft_Esd_RSSIBar_Number_of_Bars__Default;
	context->Current_Strength = Ft_Esd_RSSIBar_Current_Strength__Default;
	context->Signal_Search_Mode = Ft_Esd_RSSIBar_Signal_Search_Mode__Default;
	context->BaseValue = 0L;
	context->RepeatValue = 0L;
}

void RenderBarGraph(Ft_Esd_RSSIBar *context, int, int, int, int, ft_argb32_t, ft_argb32_t, int, int, int, int, ft_bool_t, Ft_Esd_Theme *, int, int);
void UpdateBarGraph(Ft_Esd_RSSIBar *context, int, int, int, int, int);

void Ft_Esd_RSSIBar_Update(Ft_Esd_RSSIBar *context)
{
	void *owner = context->Owner;
	ft_int16_t GlobalX = context->Widget.GlobalX;
	ft_int16_t Width = context->Widget.GlobalWidth;
	int NumberOfBar = context->Number_of_Bars(owner);
	int MinStrength = context->Min_Strength(owner);
	int MaxStrength = context->Max_Strength(owner);
	UpdateBarGraph(context, GlobalX, Width, NumberOfBar, MinStrength, MaxStrength);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context); 
}

void Ft_Esd_RSSIBar_Render(Ft_Esd_RSSIBar *context)
{
	void *owner = context->Owner;
	ft_uint8_t s = 255;
	Ft_Esd_Dl_TAG(s);
	ft_int16_t X = context->Widget.GlobalX;
	ft_int16_t Y = context->Widget.GlobalY;
	ft_int16_t Width_1 = context->Widget.GlobalWidth;
	ft_int16_t Height = context->Widget.GlobalHeight;
	ft_argb32_t DefaultColor = context->Default_Color(owner);
	ft_argb32_t FillingColor = context->Fill_Color(owner);
	int MinStrength_1 = context->Min_Strength(owner);
	int MaxStrength_1 = context->Max_Strength(owner);
	int NumberOfBars = context->Number_of_Bars(owner);
	int CurrentStrength = context->Current_Strength(owner);
	ft_bool_t SignalSearchMode = context->Signal_Search_Mode(owner);
	Ft_Esd_Theme * theme = context->Theme(owner);
	int BaseX = context->BaseValue;
	int Loop = context->RepeatValue;
	RenderBarGraph(context, X, Y, Width_1, Height, DefaultColor, FillingColor, MinStrength_1, MaxStrength_1, NumberOfBars, CurrentStrength, SignalSearchMode, theme, BaseX, Loop);
	ft_uint8_t s_1 = 255;
	Ft_Esd_Dl_TAG(s_1);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}


/* end of file */
