/*
This file is automatically generated
CelingLight1
C Source
*/

#include "CelingLight1.h"

#include "Ft_Gpu.h"
#include "CelingLight1_progmem.h"

Ft_Esd_BitmapInfo CelingLight1__Info = {
	ESD_BITMAP_DEFAULTS,
	.Width = 167, /* Padded to 168, REPEAT will not work as expected */
	.Height = 21,
	.Format = L4,
	.Stride = 84,
	.Size = 1764,
	.ProgMem = CelingLight1_bin,
	.StorageSize = ((862 + 3) >> 2),
	.Cells = 1,
	.Compressed = 1,
	.Persistent = 0,
	.Type = ESD_RESOURCE_PROGMEM,
};

Ft_Esd_BitmapCell CelingLight1(ft_uint16_t cell)
{
	return (Ft_Esd_BitmapCell){ 
		.Info = &CelingLight1__Info, 
		.Cell = cell 
	};
}


/* end of file */
