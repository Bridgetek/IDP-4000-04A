/*
Usr_GlobalVariables
C Source
*/
#ifndef Usr_GlobalVariables__H
#define Usr_GlobalVariables__H

#include "Ft_Esd.h"

//Lights settings
ESD_GLOBAL(g_AllLightsIsOn, Type = int)
ESD_GLOBAL(g_BedroomLightValue, Type = int)
ESD_GLOBAL(g_BedroomLightIsOn, Type = int)
ESD_GLOBAL(g_LivingRoomLightValue, Type = int)
ESD_GLOBAL(g_LivingRoomLightIsOn, Type = int)
ESD_GLOBAL(g_CeilingLightValue, Type = int)
ESD_GLOBAL(g_CeilingLightIsOn, Type = int)
ESD_GLOBAL(g_WarmLightValue, Type = int)
ESD_GLOBAL(g_WarmLightIsOn, Type = int)

//Air con settings
ESD_GLOBAL(g_AirconIsOn, Type = int)
ESD_GLOBAL(g_CoolValue, Type = int)
ESD_GLOBAL(g_HeatValue, Type = int)
ESD_GLOBAL(g_FanValue, Type = int)
ESD_GLOBAL(g_HumidityValue, Type = int)

//Smart Curtain settings
ESD_GLOBAL(g_CurtainIsClose, Type = int)
ESD_GLOBAL(g_CurtainOpenPercentage, Type = int)
ESD_GLOBAL(g_CurtainOpenPrevPercentage, Type = int)
ESD_GLOBAL(g_TimingCurtain1, Type = int)
ESD_GLOBAL(g_TimingCurtain2, Type = int)
ESD_GLOBAL(g_TimingCurtain3, Type = int)

//Floor Heating settings
ESD_GLOBAL(g_FloorHeatingIsOn, Type = int)
ESD_GLOBAL(g_FloorHeatingValue, Type = int)
ESD_GLOBAL(g_FloorHeatingPrevValue, Type = int)
ESD_GLOBAL(g_FloorHeatingPowerValue, Type = int)
ESD_GLOBAL(g_FloorHeatingSettingValue, Type = int)


#endif /* Usr_GlobalVariables__H */

/* end of file */
