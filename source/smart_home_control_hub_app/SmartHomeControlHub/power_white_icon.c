/*
This file is automatically generated
power_white_icon
C Source
*/

#include "power_white_icon.h"

#include "Ft_Gpu.h"
#include "power_white_icon_progmem.h"

Ft_Esd_BitmapInfo power_white_icon__Info = {
	ESD_BITMAP_DEFAULTS,
	.Width = 44,
	.Height = 44,
	.Format = L4,
	.Stride = 22,
	.Size = 968,
	.ProgMem = power_white_icon_bin,
	.StorageSize = ((429 + 3) >> 2),
	.Cells = 1,
	.Compressed = 1,
	.Persistent = 0,
	.Type = ESD_RESOURCE_PROGMEM,
};

Ft_Esd_BitmapCell power_white_icon(ft_uint16_t cell)
{
	return (Ft_Esd_BitmapCell){ 
		.Info = &power_white_icon__Info, 
		.Cell = cell 
	};
}


/* end of file */
