/*
This file is automatically generated
DO NOT MODIFY BY HAND
Usr_Spin_Image
Header
*/

#ifndef Usr_Spin_Image__H
#define Usr_Spin_Image__H

#include "Esd_Base.h"
#include "Esd_BitmapInfo.h"
#include "Ft_Esd.h"
#include "Ft_Esd_BitmapInfo.h"
#include "Ft_Esd_Image_Rotate.h"
#include "Ft_Esd_Math.h"
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

#define Usr_Spin_Image_CLASSID 0x28616813
ESD_SYMBOL(Usr_Spin_Image_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Usr_Spin_Image, Include = "Usr_Spin_Image.h", Callback, X = 0, Y = 0, Width = 400, Height = 300)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_VARIABLE(BitmapCell, Type = Esd_BitmapCell, Public)
	Esd_BitmapCell BitmapCell;
	ESD_VARIABLE(Angle, Type = int, Private)
	int Angle;
	ESD_VARIABLE(Speed, Type = int, Min = 0, Max = 65535, Public)
	int Speed;
	Ft_Esd_Image_Rotate ESD_Image_Rotate;
} Usr_Spin_Image;

void Usr_Spin_Image__Initializer(Usr_Spin_Image *context);

ESD_SLOT(Update)
void Usr_Spin_Image_Update(Usr_Spin_Image *context);

ESD_SLOT(End)
void Usr_Spin_Image_End(Usr_Spin_Image *context);

ESD_SLOT(Render)
void Usr_Spin_Image_Render(Usr_Spin_Image *context);

#endif /* Usr_Spin_Image__H */

/* end of file */
