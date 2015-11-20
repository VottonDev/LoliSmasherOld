class CNoSpread
{
public:
	void __fastcall GetSpreadFix(int &random_seed, QAngle &vIn, QAngle &vOut, C_BaseCombatWeapon*pWeapon, CBaseEntityNew*pLocal)
	{
		//m_pCVar->ConsolePrintf("%i", random_seed);
		//NormalizeAngles(vIn);
		//Vector vPunchAngle = *(Vector*)((DWORD)pLocal + gmodPUNCHANGLE);
		//vPunchAngle *= 2;
		//float len = VectorNormalize(vPunchAngle);
		//len -= (10.0 + len * 0.5) * m_pGlobals->interval_per_tick;
		//len = max(len, 0.0);
		//vPunchAngle *= len;
		RandomSeed((random_seed & 255) + 1);
		float flSpreadRad = RandomFloat(0.0f, M_PI * 2.0f);
		float flSpread = RandomFloat(0.0f, 0.02);
		float flConeRad = RandomFloat(0.0f, M_PI * 2.0f);
		float flCone = RandomFloat(0.0f, 0.f);
		Vector kek;
		kek = GetWeaponSpread(pWeapon);
		Vector pflSpread;
		pflSpread[0] = (cosf(flSpreadRad) * flSpread) + (cosf(flConeRad) * flCone);
		pflSpread[1] = (sinf(flSpreadRad) * flSpread) + (sinf(flConeRad) * flCone);
		Vector flForward, flRight, flUp;
		AngleVectors(vIn, &flForward, &flRight, &flUp);
		Vector pflSpreadDir;
		pflSpreadDir[0] = flForward[0] + (flRight[0] * pflSpread[0]) + (flUp[0] * pflSpread[1]);
		pflSpreadDir[1] = flForward[1] + (flRight[1] * pflSpread[0]) + (flUp[1] * pflSpread[1]);
		pflSpreadDir[2] = flForward[2] + (flRight[2] * pflSpread[0]) + (flUp[2] * pflSpread[1]);
		QAngle flSpreadAngles;
		VectorAngles(pflSpreadDir, flSpreadAngles);
		vOut = vIn - flSpreadAngles;
		//NormalizeAngles(vOut);
	}

private:
	float GetWeaponSpread(C_BaseCombatWeapon* pWeapon)
	{
		/*float flResult = 0.0f;

		__asm
		{
			MOV EAX, 0x4FC;
			MOV ESI, pWeapon;
			MOV EDX, DWORD PTR DS : [ESI];
			MOV EAX, DWORD PTR DS : [EDX + EAX];
			MOV ECX, ESI;
			CALL EAX;
			FSTP flResult;
		}

		return flResult;*/
		typedef float(__thiscall* fn)(void*);
		float f;
		f = VMT.getvfunc<fn>(pWeapon, /*319*/375)(pWeapon);
		return f;
	}

}; CNoSpread NoSpread;