/*
This file is automatically generated
Curtain_hand_pull
C Source
*/

#include "Curtain_hand_pull.h"

#include "Ft_Gpu.h"
#include "Curtain_hand_pull_progmem.h"

Ft_Esd_BitmapInfo Curtain_hand_pull__Info = {
	ESD_BITMAP_DEFAULTS,
	.Width = 40,
	.Height = 36,
	.Format = ARGB1555,
	.Stride = 80,
	.Size = 2880,
	.ProgMem = Curtain_hand_pull_bin,
	.StorageSize = ((719 + 3) >> 2),
	.Cells = 1,
	.Compressed = 1,
	.Persistent = 0,
	.Type = ESD_RESOURCE_PROGMEM,
};

Ft_Esd_BitmapCell Curtain_hand_pull(ft_uint16_t cell)
{
	return (Ft_Esd_BitmapCell){ 
		.Info = &Curtain_hand_pull__Info, 
		.Cell = cell 
	};
}


/* end of file */
