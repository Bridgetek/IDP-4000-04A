/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_RingSlider
Header
*/

#ifndef Ft_Esd_RingSlider__H
#define Ft_Esd_RingSlider__H

#include "Esd_Base.h"
#include "Esd_TouchTag.h"
#include "Ft_Esd.h"
#include "Ft_Esd_Layout_Fixed.h"
#include "Ft_Esd_PartialRing.h"
#include "Ft_Esd_RenderForwarder.h"
#include "Ft_Esd_Widget.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_ARRAY_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

#define Ft_Esd_RingSlider_CLASSID 0xD51AE186
ESD_SYMBOL(Ft_Esd_RingSlider_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_RingSlider, Include = "Ft_Esd_RingSlider.h", Callback, DisplayName = "ESD Ring Slider", Category = EsdWidgets, X = 0, Y = 0, Width = 400, Height = 300)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_VARIABLE(Angle, Type = ft_int16_t, Min = 0, Max = 360, Default = 90, Private)
	ft_int16_t Angle;
	ESD_VARIABLE(Max_Angle, DisplayName = "Max Angle", Type = ft_int16_t, Min = 1, Max = 360, Default = 270, Public)
	ft_int16_t Max_Angle;
	ESD_INPUT(Clockwise, Type = ft_bool_t, Default = true)
	ft_bool_t(* Clockwise)(void *context);
	ESD_INPUT(Origin, Type = int, Min = 0, Max = 360, Default = 135)
	int(* Origin)(void *context);
	ESD_INPUT(RingWidth, DisplayName = "Ring Width", Type = int, Min = 1, Max = 100, Default = 50)
	int(* RingWidth)(void *context);
	ESD_INPUT(InnerBorder, DisplayName = "Inner Border", Type = int, Min = -1, Max = 100, Default = 1)
	int(* InnerBorder)(void *context);
	ESD_INPUT(OuterBorder, DisplayName = "Outer Border", Type = int, Min = -1, Max = 100, Default = 1)
	int(* OuterBorder)(void *context);
	ESD_VARIABLE(StartAngle, Type = int, Private)
	int StartAngle;
	ESD_INPUT(BorderColor, DisplayName = "Border Color", Type = ft_argb32_t, Default = #d0cec6)
	ft_argb32_t(* BorderColor)(void *context);
	/* Clamped New Angle */
	ESD_VARIABLE(ClampedNewAngle, DisplayName = "Angle", Type = int, Min = 0, Max = 360, Default = 50, Private)
	int ClampedNewAngle;
	ESD_VARIABLE(NewAngle, Type = int, Private)
	int NewAngle;
	ESD_INPUT(SelectionColor, DisplayName = "Selection Color", Type = ft_argb32_t, Default = #0055ff)
	ft_argb32_t(* SelectionColor)(void *context);
	ESD_VARIABLE(TrackAngle, Type = int, Private)
	int TrackAngle;
	/* Background Color */
	ESD_INPUT(BackgroundColor, DisplayName = "Background Color", Type = ft_argb32_t, Default = #646464)
	ft_argb32_t(* BackgroundColor)(void *context);
	ESD_VARIABLE(StartTrackAngle, Type = int, Private)
	int StartTrackAngle;
	ESD_VARIABLE(IsTracking, Type = ft_bool_t, Private)
	ft_bool_t IsTracking;
	ESD_VARIABLE(Value, Type = ft_int16_t, Min = 0, Max = 1024, Default = 10, Public)
	ft_int16_t Value;
	ESD_VARIABLE(MaxValue, DisplayName = "Max Value", Type = ft_int16_t, Min = 10, Max = 1024, Default = 100, Public)
	ft_int16_t MaxValue;
	ESD_INPUT(KnobColor, DisplayName = "Knob Color", Type = ft_argb32_t, Default = #f7f7f7)
	ft_argb32_t(* KnobColor)(void *context);
	ESD_VARIABLE(IsOutOfBound, Type = ft_bool_t, Private)
	ft_bool_t IsOutOfBound;
	ESD_INPUT(KnobRadius, DisplayName = "Knob Radius", Type = int, Default = 25)
	int(* KnobRadius)(void *context);
	Esd_TouchTag Touch_Tag_2;
	Ft_Esd_RenderForwarder Render_Forwarder;
	Ft_Esd_Layout_Fixed Fixed_Positioning;
	Ft_Esd_PartialRing ESD_Partial_Ring;
} Ft_Esd_RingSlider;

void Ft_Esd_RingSlider__Initializer(Ft_Esd_RingSlider *context);

ESD_SLOT(Start)
void Ft_Esd_RingSlider_Start(Ft_Esd_RingSlider *context);

ESD_SLOT(Update)
void Ft_Esd_RingSlider_Update(Ft_Esd_RingSlider *context);

ESD_SLOT(End)
void Ft_Esd_RingSlider_End(Ft_Esd_RingSlider *context);

#endif /* Ft_Esd_RingSlider__H */

/* end of file */
