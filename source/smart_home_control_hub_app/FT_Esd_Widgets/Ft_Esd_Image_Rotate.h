/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Image_Rotate
Header
*/

#ifndef Ft_Esd_Image_Rotate__H
#define Ft_Esd_Image_Rotate__H

#include "Esd_Base.h"
#include "Ft_Esd.h"
#include "Ft_Esd_BitmapInfo.h"
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

#define Ft_Esd_Image_Rotate_CLASSID 0xC6B8FA07
ESD_SYMBOL(Ft_Esd_Image_Rotate_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_Image_Rotate, Include = "Ft_Esd_Image_Rotate.h", Callback, DisplayName = "ESD Image Rotate", Category = EsdWidgets, Icon = ":/icons/picture-medium.png", X = 130, Y = 44, Width = 400, Height = 300)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_VARIABLE(Color, Type = ft_argb32_t, Default = #ffffff, Public)
	ft_argb32_t Color;
	ESD_INPUT(BitmapCell, DisplayName = "Bitmap Cell", Type = Ft_Esd_BitmapCell)
	Ft_Esd_BitmapCell(* BitmapCell)(void *context);
	ESD_VARIABLE(RotateAngle, Type = ft_int32_t, Min = -65536, Max = 65535, SingleStep = 1, Public)
	ft_int32_t RotateAngle;
	ESD_VARIABLE(ScaleX, Type = ft_int32_f16_t, Default = 1, Public)
	ft_int32_f16_t ScaleX;
	ESD_VARIABLE(ScaleY, Type = ft_int32_f16_t, Default = 1, Public)
	ft_int32_f16_t ScaleY;
} Ft_Esd_Image_Rotate;

void Ft_Esd_Image_Rotate__Initializer(Ft_Esd_Image_Rotate *context);

ESD_SLOT(Render)
void Ft_Esd_Image_Rotate_Render(Ft_Esd_Image_Rotate *context);

#endif /* Ft_Esd_Image_Rotate__H */

/* end of file */
