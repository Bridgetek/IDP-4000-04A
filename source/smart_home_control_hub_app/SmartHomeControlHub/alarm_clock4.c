/*
This file is automatically generated
alarm_clock4
C Source
*/

#include "alarm_clock4.h"

#include "Ft_Gpu.h"
#include "alarm_clock4_progmem.h"

Ft_Esd_BitmapInfo alarm_clock4__Info = {
	ESD_BITMAP_DEFAULTS,
	.Width = 64,
	.Height = 64,
	.Format = PALETTED8,
	.Stride = 64,
	.Size = 4096,
	.ProgMem = alarm_clock4_index_bin,
	.StorageSize = ((2219 + 3) >> 2),
	.PaletteProgMem = alarm_clock4_lut_raw,
	.Cells = 1,
	.Compressed = 1,
	.Persistent = 0,
	.Type = ESD_RESOURCE_PROGMEM,
};

Ft_Esd_BitmapCell alarm_clock4(ft_uint16_t cell)
{
	return (Ft_Esd_BitmapCell){ 
		.Info = &alarm_clock4__Info, 
		.Cell = cell 
	};
}


/* end of file */
