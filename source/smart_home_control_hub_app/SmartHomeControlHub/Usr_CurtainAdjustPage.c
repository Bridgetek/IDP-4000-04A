#include "Ft_Esd.h"
#include "Usr_CurtainAdjustPage.h"
#include <string.h>

static char text[20] = { '\0' };
static int percentage = 100; // Curtain closed
//extern int g_CurtainOpenPercentage;

ESD_FUNCTION(GetPercentage, Type = int)
int GetPercentage(void)
{
	return percentage;
}

ESD_METHOD(UpdatePercentage, Context = Usr_CurtainAdjustPage)
void UpdatePercentage(Usr_CurtainAdjustPage *context)
{
	percentage += context->Delta;
}

ESD_FUNCTION(GetTextDisplay, Type = char *)
ESD_PARAMETER(percentage, Type = int)
char *GetTextDisplay(int percentage)
{
	if (percentage < 1)
	{
		sprintf(text, "%s", "Curtain is Opened");
	}
	else if (percentage >= 100)
	{
		sprintf(text, "%s", "Curtain is Closed");
	}
	else
	{
		sprintf(text, "%d %%", percentage);
	}
	return text;
}

static ft_bool_t sound = 0;
ESD_METHOD(LongTap_Detected, Context = Usr_CurtainAdjustPage)
void LongTap_Detected(Usr_CurtainAdjustPage *context)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Gpu_Hal_Wr8(phost, REG_VOL_SOUND, 255); // set the volume max
	Ft_Gpu_Hal_Wr16(phost, REG_SOUND, (65 << 8) | 0x49); // Sound: 0x49 Midi: 65
	Ft_Gpu_Hal_Wr8(phost, REG_PLAY, 1);
	sound = 1;
}

ESD_METHOD(Usr_CurtainAdjustPage_Update_Signal, Context = Usr_CurtainAdjustPage)
void Usr_CurtainAdjustPage_Update_Signal(Usr_CurtainAdjustPage *context)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	if (sound && !Ft_Gpu_Hal_Rd8(phost, REG_PLAY))
	{
		Ft_Gpu_Hal_Wr8(phost, REG_VOL_SOUND, 0); // set the volume 0
		Ft_Gpu_Hal_Wr16(phost, REG_SOUND, 0x60); // Mute
		Ft_Gpu_Hal_Wr8(phost, REG_PLAY, 1);
		sound = 0;
	}
}


ESD_METHOD(Usr_CurtainAdjustPage_SetPercemtage_Signal, Context = Usr_CurtainAdjustPage)
void Usr_CurtainAdjustPage_SetPercemtage_Signal(Usr_CurtainAdjustPage *context)
{
	// ...
	percentage = context->PercentageClosed;
	//g_CurtainOpenPercentage = context->PercentageClosed;
}
