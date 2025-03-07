#include "Ft_Esd.h"
#include "AppScreen.h"

ESD_METHOD(AppScreen_Update_Signal, Context = AppScreen)
void AppScreen_Update_Signal(AppScreen *context)
{
	// dataRotary 0: no action, 1: right, -1: left.
	int dataRotary = 0;
	encoder_read(&dataRotary);
	if(dataRotary == 1)
	{
		//Call right here
		AppScreen_Right(context);
	}
	else if(dataRotary == -1)
	{
		//Call left here
		AppScreen_Left(context);
	}
	// dataPush 0: no action, 1: press, 2: release, -1:  not success
	int dataButton = 0;
	button_read(&dataButton);
	//Call button release
	if(dataButton == 2)
	{
		//Call Push here
		AppScreen_Push(context);
	}
	
}