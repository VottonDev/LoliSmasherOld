byte sendpacketedited;
class CVerifiedUserCmd
{
public:
	GMODCUserCmd	m_cmd;
	CRC32_t		m_crc;
};
CUtils Utilities;
void VectorAngles(Vector *forward, Vector *angles)
{
	float   tmp, yaw, pitch;

	if (forward->y == 0 && forward->x == 0)
	{
		yaw = 0;
		if (forward->z > 0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
	{
		yaw = (float)(atan2(forward->y, forward->x) * 180.0 / M_PI);

		if (yaw < 0) yaw += 360.0;

		tmp = (float)sqrt(forward->x*forward->x + forward->y*forward->y);

		pitch = (float)(atan2(forward->z, tmp) * 180 / M_PI);
	}

	angles->x = -pitch;
	angles->y = yaw;
	angles->z = 0;
}
void __stdcall CL_FixMove(GMODCUserCmd* cmd, Vector viewangles)
{
	Vector move, movenorm, dir, set;
	Vector movenormang, adjusted;

	float len;

	move.Init(cmd->forwardmove, cmd->sidemove, cmd->upmove);

	movenorm = move;

	VectorNormalize(movenorm);

	len = move.Length();

	VectorAngles(&movenorm, &movenormang);

	if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
	{
		if (viewangles.x >= 0.0f && viewangles.x <= 89.0f)
		{
			viewangles.x = cmd->viewangles.x + 180.0f;
		}
		if (viewangles.x <= 0.0f && viewangles.x >= -89.0f)
		{
			viewangles.x = cmd->viewangles.x - 180.0f;
		}
	}

	adjusted = movenormang + (cmd->viewangles - viewangles);

	AngleVectors((QAngle&)adjusted, &dir);

	set = dir * len;

	if ((cmd->viewangles.x > 89.0f) || (cmd->viewangles.x < -89.0f))
		cmd->forwardmove = set.x;
	else if ((cmd->viewangles.x == 89.0f || cmd->viewangles.x == -89.0f))
		cmd->forwardmove = -set.x;
	else
		cmd->forwardmove = set.x;

	if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
		cmd->sidemove = -set.y;
	else
		cmd->sidemove = set.y;
}

int ChokedCommands = 0;
void __stdcall hkCreateMove(int sequencenumber, float Input, bool Active)
{
	void* _ebp;
	__asm mov _ebp, ebp;
	byte* sendpacket = (byte*)(*(char**)_ebp - 0x1);
	*sendpacket = true;
	if ( ChokedCommands <= 0 )
		ChokedCommands = 7;
	else
	{
		ChokedCommands--;
		*sendpacket = false;
	}

	orgCreateMove(sequencenumber, Input, Active);
	GMODCUserCmd* UserCmd = (GMODCUserCmd*)Interfaces.Input->GetUserCmd(sequencenumber);
	Vector organg = UserCmd->viewangles;
	CBaseEntityNew* me = (CBaseEntityNew*)Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());

	if (!(me->GetFlags() & FL_ONGROUND) && UserCmd->buttons & IN_JUMP)
	{
		if (UserCmd->mousedx < 0)
			UserCmd->sidemove = -10000.f;
		if (UserCmd->mousedx > 0)
			UserCmd->sidemove = 10000.f;
	}
	if (UserCmd->buttons & IN_JUMP)
	{
		if (!(me->GetFlags() & FL_ONGROUND))
			UserCmd->buttons &= ~IN_JUMP;
	}
	Misc.SpeedHack(_ebp, 6);
	if (Variables.GetVar("aimbot_enabled")->GetValue())
		Aimbot.DoAimbot(UserCmd);
	float flServerTime = (float)*(int*)((DWORD)me + 0x2558) * Interfaces.Globals->interval_per_tick;
	//found this shit online
	DWORD weaponh = *reinterpret_cast<DWORD*>((DWORD)me + 0x21e0);
	if (!weaponh)
	{
		return;
	}
	int index = weaponh & 0xFFF;
	C_BaseCombatWeapon *weapon = (C_BaseCombatWeapon*)Interfaces.ClientEntList->GetClientEntity(index);
	if (!weapon)
	{
		return;
	}
	//cout << GetWeaponSpread(weapon) << endl;
	float flNextPrimaryAttack = *reinterpret_cast<float*>(((DWORD)weapon) + 0x17A0/*flNextPrimaryAttack*/);
	if (!(UserCmd->buttons & IN_ATTACK))
	{
		
		if (*sendpacket == 0)
		{
			UserCmd->viewangles.x = -181;
			UserCmd->viewangles.y = organg.y + 90.f;
		}
		else
		{
			UserCmd->viewangles.x = 85;
			UserCmd->viewangles.y = organg.y - 90.f;
		}
	}
	/*else
	{
		
		if (flNextPrimaryAttack < flServerTime)
			*sendpacket = true;
	}*/
	CL_FixMove(UserCmd, organg);
	QAngle addang;
	//NoSpread.GetSpreadFix(UserCmd->random_seed, (QAngle&)UserCmd->viewangles, addang, weapon, me);
	//UserCmd->viewangles += (Vector&)addang;
	CVerifiedUserCmd *VerifiedCommmandList = *reinterpret_cast<CVerifiedUserCmd**>((DWORD)Interfaces.Input + 0xC8);
	CVerifiedUserCmd *VerifiedCommand = &VerifiedCommmandList[sequencenumber % 90];
	VerifiedCommand->m_cmd = *UserCmd;
	VerifiedCommand->m_crc = CRC32_ProcessSingleBuffer(UserCmd, sizeof(UserCmd));
	//Keep this at the very end
}