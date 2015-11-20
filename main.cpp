#include "sdk.h"
#include "mmsystem.h"
#include "netvarsgreat.h"
#pragma comment(lib, "Winmm.lib")
class GameEventEar : public IGameEventListener2
{
	void FireGameEvent(IGameEvent* event)
	{
		if (Q_strcmp(event->GetName(), "player_hurt") == 0)
		{
			int victimID = event->GetInt("userid");
			int attackerID = event->GetInt("attacker");
			int damage = event->GetInt("damageamount");

			player_info_s pVictimInfo;
			player_info_s pAttackerInfo;

			Interfaces.Engine->GetPlayerInfo(Interfaces.Engine->GetPlayerForUserID(victimID), &pVictimInfo);

			Interfaces.Engine->GetPlayerInfo(Interfaces.Engine->GetPlayerForUserID(attackerID), &pAttackerInfo);

			IClientEntity* pVictim = (IClientEntity*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetPlayerForUserID(victimID));
			IClientEntity* pAttacker = (IClientEntity*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetPlayerForUserID(attackerID));
			CBaseEntityNew* me = (CBaseEntityNew*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
			if (!me)
				return;
			if (pVictim && pAttacker)
			{
				if (pAttacker->entindex() == me->Index())
				{
					std::string sLeftPath = "G:\\Music\\";
					//std::string sUserName = getenv("USERNAME");
					std::string sRightPath = "\\h.wav";
					std::string sFullPath = sLeftPath + sRightPath;
					PlaySoundA(sFullPath.c_str(), NULL, SND_ASYNC);
					//Msg("Lele");
				}
			}
		}
	}
} Ear;
class GameEventKilled : public IGameEventListener2
{
	void FireGameEvent(IGameEvent* event)
	{
		if (Q_strcmp(event->GetName(), "player_death") == 0)
		{
			short victimID = event->GetInt("userid");
			short attackerID = event->GetInt("attacker");

			player_info_s pVictimInfo;
			player_info_s pAttackerInfo;

			Interfaces.Engine->GetPlayerInfo(Interfaces.Engine->GetPlayerForUserID(victimID), &pVictimInfo);

			Interfaces.Engine->GetPlayerInfo(Interfaces.Engine->GetPlayerForUserID(attackerID), &pAttackerInfo);

			IClientEntity* pVictim = (IClientEntity*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetPlayerForUserID(victimID));
			IClientEntity* pAttacker = (IClientEntity*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetPlayerForUserID(attackerID));
			CBaseEntityNew* me = (CBaseEntityNew*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
			if (!me)
				return;
			if (pVictim && pAttacker)
			{
				if (pAttacker->entindex() == me->Index())
				{
					char kek[1024];
					sprintf(kek, "say %s JUST GOT FUCKED", pVictimInfo.name);
					Interfaces.Engine->ClientCmd(kek);
					Msg("kekkeke\n");
				}
			}
		}
	}
}Killed;
class AllGameEvents : public IGameEventListener2
{
	void FireGameEvent(IGameEvent* event)
	{
		printf("%s\n", event->GetName());
	}
}Listenerr;
void FixAA(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float flPitch = pData->m_Value.m_Float;
	if (flPitch > 89)
	{
		flPitch = 270;
	}
	if (flPitch < -89)
	{
		flPitch = 90;
	}

	*(float*)pOut = flPitch;
}
void MainThread()
{
	// Aimbot
	Variables.CreateVar( "aimbot_enabled" );
	Variables.CreateVar( "aimbot_ignoreteam" );
	Variables.CreateVar( "aimbot_ignorefriends" );
	Variables.CreateVar( "aimbot_nextshot" );
	Variables.CreateVar( "aimbot_loudaim" );
	// Visuals
	Variables.CreateVar( "visuals_showplayers" );
	Variables.CreateVar( "visuals_use3dbox" );
	Variables.CreateVar( "visuals_healthbars" );
	Variables.CreateVar( "visuals_showents" );
	Variables.CreateVar( "visuals_crosshair" );
	// Misc
	Variables.CreateVar( "misc_spreadcompensation" );
	Variables.CreateVar( "misc_cacsafe" );
	Variables.CreateVar( "misc_speedhack" );
	Variables.CreateVar( "misc_speedfactor" );
	Variables.CreateVar( "misc_bunnyhop" );
	Variables.CreateVar( "misc_autostrafe" );
	Variables.CreateVar( "misc_hitsounds" );
	// HvH
	Variables.CreateVar( "hvh_aaa" );
	Variables.CreateVar( "hvh_aptaaa" );
	Variables.CreateVar( "hvh_aa" );
	Variables.CreateVar( "hvh_aptaa" );
	Variables.CreateVar( "hvh_yawtype" );
	Variables.CreateVar( "hvh_pitchtype" );
	Variables.CreateVar( "hvh_fakeduck" );
	Variables.CreateVar( "hvh_fakelag" );
	Variables.CreateVar( "hvh_fakelagfactor" );
	Variables.CreateVar( "hvh_killstreaks" );
	// Colors
	Variables.CreateVar( "color_menur" );
	Variables.CreateVar( "color_menug" );
	Variables.CreateVar( "color_menub" );
	Variables.CreateVar( "color_friendr" );
	Variables.CreateVar( "color_friendg" );
	Variables.CreateVar( "color_friendb" );
	Variables.CreateVar( "color_teamr" );
	Variables.CreateVar( "color_teamg" );
	Variables.CreateVar( "color_teamb" );
	Variables.CreateVar( "color_enemyr" );
	Variables.CreateVar( "color_enemyg" );
	Variables.CreateVar( "color_enemyb" );

	Console.Initialize();
	Interfaces.GetInterfaces();
	Hooks.GetHooks();
	for (int i = 0; i < 99; i++)
		Msg("\n");
	Msg("[LoliSmasher]: Loaded!\n");
	CNetworkedVariableManager *netvars = new CNetworkedVariableManager();
	netvars->HookProp("DT_HL2MP_Player", "m_angEyeAngles[0]", FixAA);
	Interfaces.GameEventManager->AddListener(&Ear, "player_hurt", false);
	Interfaces.GameEventManager->AddListener(&Listenerr, "*", false);
}

void MenuThread()
{
	CMenuSystem();
	for(;;)
		MenuThink();
}

BOOL WINAPI DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(Instance);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MenuThread, NULL, NULL, NULL);
	}
	return true;
}