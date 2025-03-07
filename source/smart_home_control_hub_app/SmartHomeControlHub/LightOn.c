/*
This file is automatically generated
LightOn
C Source
*/

#include "LightOn.h"

#include "Ft_Gpu.h"
#include "LightOn_progmem.h"

Ft_Esd_BitmapInfo LightOn__Info = {
	ESD_BITMAP_DEFAULTS,
	.Width = 74,
	.Height = 35,
	.Format = L4,
	.Stride = 37,
	.Size = 1295,
	.ProgMem = LightOn_bin,
	.StorageSize = ((382 + 3) >> 2),
	.Cells = 1,
	.Compressed = 1,
	.Persistent = 0,
	.Type = ESD_RESOURCE_PROGMEM,
};

Ft_Esd_BitmapCell LightOn(ft_uint16_t cell)
{
	return (Ft_Esd_BitmapCell){ 
		.Info = &LightOn__Info, 
		.Cell = cell 
	};
}


/* end of file */
