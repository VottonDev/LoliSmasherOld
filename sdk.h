#pragma once

#define GAME_DLL
#define CLIENT_DLL

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)  
#define IN_SPEED		(1 << 17)	
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)	
#define IN_WEAPON1		(1 << 20)	
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)

// Some libraries
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio>
//#include <boost/shared_ptr.hpp> // wtf lmao

// SDK
#include "public/tier0/wchartypes.h"
#include "public/cdll_int.h"
#include "public/iprediction.h"
#include "public/bone_setup.h"
#include "public/icliententitylist.h"
#include "public/ienginevgui.h"
#include "public/IGameUIFuncs.h"
#include "public/dlight.h"
#include "public/r_efx.h" 
#include "public/igameevents.h"
#include "public/view_shared.h"
#include "public/inetchannelinfo.h"
#include "public/iachievementmgr.h"
#include "public/steam/steam_api.h"
#include "public/steam/isteamuserstats.h"
#include "game/client/imessagechars.h"
#include "game/client/iclientmode.h"
#include "game/client/cliententitylist.h"
#include "game/client/cdll_client_int.h"
#include "game/client/cbase.h"
#include "game/client/c_baseanimating.h"
#include "game/client/c_basecombatweapon.h"
#include "game/client/c_baseplayer.h"
#include "game/client/enginesprite.h"
#include "game/client/input.h"
#include "game/client/c_playerresource.h"
#include "game/client/iviewrender.h"
#include "game/client/viewrender.h"
#include "game/client/game_controls/commandmenu.h"
#include "game/client/hudelement.h"
#include "public/engine/ivmodelrender.h"
#include "public/engine/ivdebugoverlay.h"
#include "public/engine/ivmodelinfo.h"
#include "public/engine/IEngineTrace.h"
#include "public/engine/IEngineSound.h"
#include "public/materialsystem/imaterialsystemstub.h"
#include "public/materialsystem/itexture.h"
#include "public/materialsystem/IMaterialVar.h"
#include "public/tier1/checksum_md5.h"
#include "public/matsys_controls/matsyscontrols.h"
#include "public/vgui/IClientPanel.h"
#include "public/vgui/IPanel.h"
#include "public/vgui/ISurface.h"
#include "public/vgui/ILocalize.h"
#include "public/collisionutils.h"
#include "public/vstdlib/random.h"
#include "public/vgui_controls/Panel.h"
#include "public/VGuiMatSurface/IMatSystemSurface.h"
#include "public/mathlib/vector.h"
#include "game/shared/usermessages.h"
#include "game/shared/basecombatweapon_shared.h"
#include "game/shared/takedamageinfo.h"
#include "game/shared/igamemovement.h"

class GMODCUserCmd
{
public:
	char _0x0000[4];
	float command_number; //0x0004 
	float tick_count; //0x0008 
	Vector viewangles; //0x000C 
	float forwardmove; //0x0018 
	float sidemove; //0x001C 
	float upmove; //0x0020 
	int buttons; //0x0024 
	char _0x0028[12];
	int random_seed; //0x0034 
	__int16 mousedx; //0x0038 
	__int16 mousey; //0x003A 
	char _0x003C[288];

};//Size=0x015C
// Libraries
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "tier1.lib")
#pragma comment(lib, "tier2.lib")
#pragma comment(lib, "tier3.lib")
#pragma comment(lib, "mathlib.lib")
#pragma comment(lib, "vstdlib.lib")

typedef void(__stdcall* CreateMoveFn)(int, float, bool);
typedef void(__thiscall* PaintTraverseFn)(void*,VPANEL, bool, bool);
extern CreateMoveFn orgCreateMove;
extern PaintTraverseFn orgPaintTraverse;
//OUR FILES
#include "vmt.h"
#include "baseentity.h"
#include "cliententlist.h"
#include "customccvar.h"
#include "cengine.h"
#include "interfaces.h"
#include "variables.h"
#include "console.h"
#include "utils.h"
#include "misc.h"
#include "Aimbot.h"
#include "visuals.h"
#include "netvarsgreat.h"
#include "menu/menu.h"

#include "painttraverse.h"
#include "createmove.h"
#include "hooks.h"