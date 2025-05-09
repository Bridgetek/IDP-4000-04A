/*
This file is automatically generated
humid_icon
Header
*/

#ifndef humid_icon__H
#define humid_icon__H

#ifndef ESD_FUNCTION
#define ESD_FUNCTION(name, ...)
#endif

#include "Ft_DataTypes.h"
#include "Ft_Esd_BitmapInfo.h"

Ft_Esd_BitmapCell humid_icon(ft_uint16_t cell);

extern Ft_Esd_BitmapInfo humid_icon__Info;

ESD_FUNCTION(humid_icon_0, Type = Ft_Esd_BitmapCell, DisplayName = "humid_icon", Include = "humid_icon.h", Category = _GroupUserResources, Icon = ":/icons/image.png", Macro)
#define humid_icon_0() ((Ft_Esd_BitmapCell){ .Info = &humid_icon__Info, .Cell = 0 })

#endif /* humid_icon__H */

/* end of file */
