#include "Ft_Esd.h"
#include "Usr_LightWidget.h"

extern ESD_CORE_EXPORT EVE_HalContext *Esd_Host;

ESD_METHOD(Usr_LightWidget_Render_Signal, Context = Usr_LightWidget)
void Usr_LightWidget_Render_Signal(Usr_LightWidget *context)
{
	EVE_HalContext *phost = Esd_GetHost();
	int gX = context->Widget.GlobalX * 16;;
	int gY = context->Widget.GlobalY * 16;
	
	EVE_CoCmd_dl(phost, COLOR_RGB(122, 140, 152));
	EVE_CoCmd_dl(phost, LINE_WIDTH(30));
	EVE_CoCmd_dl(phost, BEGIN(LINES));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 576, gY));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 576, gY + 200));

	EVE_CoCmd_dl(phost, LINE_WIDTH(100));
	EVE_CoCmd_dl(phost, BEGIN(LINES));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 576, gY + 180));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 576, gY + 180));
	EVE_CoCmd_dl(phost, END());

	EVE_CoCmd_dl(phost, POINT_SIZE(576));
	EVE_CoCmd_dl(phost, BEGIN(POINTS));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 577, gY + 768));
	EVE_CoCmd_dl(phost, END());
	EVE_CoCmd_dl(phost, BLEND_FUNC(ZERO, ONE_MINUS_SRC_ALPHA));
	EVE_CoCmd_dl(phost, COLOR_RGB(255, 255, 127));
	EVE_CoCmd_dl(phost, BEGIN(RECTS));
	EVE_CoCmd_dl(phost, VERTEX2F(gX, 920));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 1152, gY + 1300));
	EVE_CoCmd_dl(phost, END());
	EVE_CoCmd_dl(phost, BLEND_FUNC(ONE_MINUS_DST_ALPHA, ONE));
	EVE_CoCmd_dl(phost, COLOR_RGB(255, 255, 0));
	EVE_CoCmd_dl(phost, POINT_SIZE(180));
	EVE_CoCmd_dl(phost, BEGIN(LINES));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 1216, gY + 1744));
	EVE_CoCmd_dl(phost, END());
	EVE_CoCmd_dl(phost, BEGIN(POINTS));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 576, gY + 848));
	EVE_CoCmd_dl(phost, END());

	EVE_CoCmd_dl(phost, COLOR_RGB(243, 112, 33));
	EVE_CoCmd_dl(phost, LINE_WIDTH(30));
	EVE_CoCmd_dl(phost, BEGIN(LINES));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 272, gY + 1024));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 112, gY + 1216));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 300, gY + 1300));
	EVE_CoCmd_dl(phost, VERTEX2F(gX + 400, gY + 1120));
	EVE_CoCmd_dl(phost, END());
}
