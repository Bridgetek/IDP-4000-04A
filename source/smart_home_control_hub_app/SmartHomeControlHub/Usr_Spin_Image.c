#include "Ft_Esd.h"
#include "Usr_Spin_Image.h"

ESD_METHOD(Usr_Spin_Image_Render_Signal, Context = Usr_Spin_Image)
void Usr_Spin_Image_Render_Signal(Usr_Spin_Image *context)
{
	context->Angle = context->Angle + context->Speed;
	//eve_printf("Usr_Spin_Image_Render_Signal %d\n", context->Angle);
	if(context->Angle > 65535)
	{
		context->Angle = context->Angle%65535;
	}
}