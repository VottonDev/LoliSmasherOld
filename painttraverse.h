using namespace vgui;
#define DM Visuals
enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};
void DrawEsp(int i)
{
	CBaseEntityNew* target = (CBaseEntityNew*)Interfaces.ClientEntList->GetClientEntity(i);
	CBaseEntityNew* me = (CBaseEntityNew*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
	if (!me)
		return;
	if (i == me->Index())
		return;
	player_info_t info;
	if (!target || target->IsDormant() || !target->isAlive() || !Interfaces.Engine->GetPlayerInfo(i, &info))
		return;
	Vector pos = target->GetAbsOrigin();
	Vector mins = target->OBBMins();
	Vector maxs = target->OBBMaxs();
	//#rgb(231, 76, 60)
	DM.Draw3DBox(pos + mins, pos + maxs, target->Index() == Aimbot.GetTarget() ? Color(231, 76, 60, 200) : Color(0,255,0,255));
}
void __fastcall hkPaintTraverse(void* thisptr, void*,VPANEL panel, bool frp, bool allwfr)
{
	orgPaintTraverse(thisptr,panel, frp, allwfr);
	static VPANEL OverlayPopupPanel;
	static bool runonce = false;
	if (OverlayPopupPanel == NULL) { 
		const char* panelName = Interfaces.Panel->GetClassName(panel);
		if (panelName[0] == 'O' && panelName[7] == 'P') { 
			OverlayPopupPanel = panel; 
		}
	}
	if (panel == OverlayPopupPanel)
	{

		MenuPaint();

		if (!runonce)
		{
			Visuals.MenuFont = Interfaces.Surface->CreateFont();
			Interfaces.Surface->SetFontGlyphSet(Visuals.MenuFont, "Arial", 20, 500, 0, 0, FONTFLAG_ANTIALIAS);

			Visuals.MediumMenuFont = Interfaces.Surface->CreateFont();
			Interfaces.Surface->SetFontGlyphSet(Visuals.MediumMenuFont, "Arial", 16, 500, 0, 0, FONTFLAG_ANTIALIAS);

			Visuals.SmallMenuFont = Interfaces.Surface->CreateFont();
			Interfaces.Surface->SetFontGlyphSet(Visuals.SmallMenuFont, "Arial", 14, 500, 0, 0, FONTFLAG_ANTIALIAS);

			Visuals.font = Interfaces.Surface->CreateFont();
			Interfaces.Surface->SetFontGlyphSet(Visuals.font, "Arial", FONT_HEIGHT, 500, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
			runonce = true;
		}
		Visuals.DrawWatermark();
		for (int i = 0; i < 64; i++)
		{
			DrawEsp(i);
		}
	}
}