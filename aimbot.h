struct sPlayerList{
	float oldtick;
	float losttick;
};
sPlayerList PlayerList[64];
class CAimbot
{
public:
	CAimbot();
	int __stdcall GetTarget();
	void __stdcall DropTarget();
	bool __stdcall GetVisible(Vector& start, Vector& end, CBaseEntityNew* target);
	void __stdcall DoAimbot(GMODCUserCmd* UserCmd);
	bool __stdcall GetHitboxPosition(int Hitbox, Vector& HitboxPos, CBaseEntityNew* target);
	inline bool __stdcall GetHitboxPosition(int HitBox, Vector& Origin, int Index);
	float __stdcall flGetDistance(Vector a, Vector b)
	{
		Vector retn;
		VectorSubtract(a, b, retn);
		return retn.Length();
	}
	/*Broken, original src: http://hastebin.com/ogudijumed.coffee and http://hastebin.com/iwebudezox.coffee */
	void ExtraPolation(CBaseEntityNew* pLocal, CBaseEntityNew *pEntity, Vector &m_vecPosition, Vector &vEyePos, int Index)
	{
		if (!pLocal || !pEntity || pLocal->IsDormant() || pEntity->IsDormant() || !pLocal->isAlive() || !pEntity->isAlive())
			return;
		Vector vOld[65];
		Vector vOldMe;
		Vector vAccel[65];
		Vector vMyAccel;
		Vector vecEnemyVelocity = pEntity->Velocity();
		Vector vMyVel = pLocal->Velocity();
		Vector vDelta = vecEnemyVelocity - vOld[Index];
		try
		{
			vOld[Index] = vecEnemyVelocity;
			if (vDelta != Vector(0.0f, 0.0f, 0.0f))
			{
				vAccel[Index] = vDelta;
			}

			Vector vDeltaMe = vMyVel - vOldMe;
			vOldMe = vMyVel;

			if (vDeltaMe != Vector(0.0f, 0.0f, 0.0f))
			{
				vMyAccel = vDeltaMe;
			}

			float flTick = Interfaces.Globals->interval_per_tick;
			int iFakeLagCmd = PlayerList[Index].losttick;

			if (iFakeLagCmd > 5.0f)
			{
				flTick += Interfaces.Globals->interval_per_tick * PlayerList[Index].losttick;

				if (vAccel[Index] != Vector(0.0f, 0.0f, 0.0f) || vMyAccel != Vector(0.0f, 0.0f, 0.0f))
				{
					Vector vDivide;
					VectorDivide((vAccel[Index] - vMyAccel) * sqrt(flTick) + (vecEnemyVelocity - vMyVel) * flTick + m_vecPosition - vEyePos, 0.5f, vDivide);
					m_vecPosition -= vDivide;
					Interfaces.Cvar->FindVar("cl_interp")->SetValue("0.695");
					Interfaces.Cvar->FindVar("cl_updaterate")->SetValue("1048576");
					Interfaces.Cvar->FindVar("cl_cmdrate")->SetValue("1048576");
				}
			}

			if (iFakeLagCmd <= 5.0f && iFakeLagCmd > 1.0f)
			{
				flTick += Interfaces.Globals->interval_per_tick * PlayerList[Index].losttick;

				if (vAccel[Index] != Vector(0.0f, 0.0f, 0.0f) || vMyAccel != Vector(0.0f, 0.0f, 0.0f))
				{
					Vector vDivide;
					VectorDivide((vAccel[Index] - vMyAccel) * sqrt(flTick) + (vecEnemyVelocity - vMyVel) * flTick + m_vecPosition - vEyePos, 0.5f, vDivide);
					m_vecPosition -= vDivide;
					Interfaces.Cvar->FindVar("cl_interp")->SetValue("0.7");
					Interfaces.Cvar->FindVar("cl_updaterate")->SetValue("66");
					Interfaces.Cvar->FindVar("cl_cmdrate")->SetValue("66");
				}
			}

			if (iFakeLagCmd == 1.0f)
			{
				if (vAccel[Index] != Vector(0.0f, 0.0f, 0.0f) || vMyAccel != Vector(0.0f, 0.0f, 0.0f))
				{
					Vector vDivide;
					VectorDivide((vAccel[Index] - vMyAccel) * sqrt(flTick) + (vecEnemyVelocity - vMyVel) * flTick + m_vecPosition - vEyePos, 0.5f, vDivide);
					m_vecPosition += vDivide;
					Interfaces.Cvar->FindVar("cl_updaterate")->SetValue("67");
					Interfaces.Cvar->FindVar("cl_cmdrate")->SetValue("67");
					Interfaces.Cvar->FindVar("cl_interp")->SetValue("1");
				}
			}
		}
		catch (...)
		{
			Msg("Something fucked up!\n");
		}
		
	}
private:
	int Target;
	float BestDist;
	Vector player;
	Vector PredictedPosition;
}; CAimbot Aimbot;

CAimbot::CAimbot()
{
	BestDist = 99999.f;
	Target = -1;
}
void __stdcall CAimbot::DropTarget()
{
	BestDist = 99999.f;
	Target = -1;
}
int __stdcall CAimbot::GetTarget()
{
	return Target;
}
void __stdcall CAimbot::DoAimbot(GMODCUserCmd* UserCmd)
{
	DropTarget();
	CBaseEntityNew* me = Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
	for (int i = 1; i < 64; ++i)
	{
		if (i == Interfaces.Engine->GetLocalPlayer())
			continue;

		CBaseEntityNew* target = Interfaces.ClientEntList->GetClientEntity(i);
		player_info_t info;
		//Calls from left->right so we wont get an access violation error
		Vector pos;
		if (!target || target->IsDormant() || !target->isAlive() || !Interfaces.Engine->GetPlayerInfo(i, &info) || !GetHitboxPosition(6,pos,target) || flGetDistance(pos, me->GetEyePosition()) > BestDist || !GetVisible(me->GetEyePosition(), pos, target))
			continue;
		pos += Vector(0, 0, 6);
		BestDist = flGetDistance(pos, me->GetEyePosition());
		Target = i;
		//ExtraPolation(me, target, pos, me->GetEyePosition(), target->Index());
		PredictedPosition = pos - (me->Velocity() * Interfaces.Globals->interval_per_tick);
		//PredictedPosition = pos;
	}
	if (Target == -1)
		return;
	
	VectorAngles(PredictedPosition - me->GetEyePosition(), (QAngle&)UserCmd->viewangles);
	while (UserCmd->viewangles.x > 89.f)
		UserCmd->viewangles.x -= 360.f;
	//Interfaces.Engine->SetViewAngles(UserCmd->viewangles);
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
	if (flServerTime > flNextPrimaryAttack)
		UserCmd->buttons |= IN_ATTACK;
}
bool __stdcall CAimbot::GetVisible(Vector& start, Vector& end, CBaseEntityNew* target)
{
	player_info_t info;
	trace_t trace;
	Ray_t ray;
	ray.Init(start, end);
	Interfaces.Trace->TraceRay(ray, MASK_SHOT, NULL, &trace);

	if (trace.fraction  == 1.f)
		return true;

	if (trace.m_pEnt && target)
	{
		if (trace.m_pEnt->index == 0 || trace.allsolid)
			return false;
		if ((Interfaces.Engine->GetPlayerInfo(trace.m_pEnt->index, &info) || target->Index() == trace.m_pEnt->index) && trace.fraction > .97f)
			return true;
	}
	return false;
}
bool __stdcall CAimbot::GetHitboxPosition(int Hitbox, Vector& HitboxPos, CBaseEntityNew* target)
{
	if (!target || target->IsDormant())
		return false;
	VMatrix matrix[128];
	if (!target->SetupBones(matrix, 128, 0x100, 0))
		return false;
	HitboxPos = Vector(matrix[Hitbox][0][3], matrix[Hitbox][1][3], matrix[Hitbox][2][3]);
	return true;
}
inline bool __stdcall CAimbot::GetHitboxPosition(int HitBox, Vector& Origin, int Index)
{
	if (HitBox < 0 || HitBox >= 20)
		return false;
	matrix3x4_t pmatrix[128];

	CBaseEntityNew* Entity = Interfaces.ClientEntList->GetClientEntity(Index);
	if (!Entity)
		return false;
	if (Entity->IsDormant())
		return false;
	const model_t* Model = Entity->GetModel();
	if (!Model)
		return false;
	studiohdr_t *pStudioHdr = Interfaces.ModelInfo->GetStudiomodel(Model);
	if (!pStudioHdr)
		return false;
	if (!Entity->SetupBones((VMatrix*)pmatrix, 128, BONE_USED_BY_HITBOX, 0))
		return false;
	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet(0);
	if (!set)
		return false;
	mstudiobbox_t* pBox = NULL;
	pBox = pStudioHdr->pHitbox(HitBox, NULL);
	Vector min, max;
	QAngle angles;
	MatrixAngles(pmatrix[pBox->bone], angles, Origin);
	VectorTransform(pBox->bbmin, pmatrix[pBox->bone], min);
	VectorTransform(pBox->bbmax, pmatrix[pBox->bone], max);
	Origin = (min + max) * 0.5f;

	return true;
}