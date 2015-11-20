class CBaseEntityNew
{
public:
	float Friction()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x25c);
	}
	bool IsCrouching()
	{
		int flags = this->GetFlags();
		return (flags & FL_DUCKING);
	}
	Vector Velocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0xf4);
	}

	int Health()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x90);
	}
	float TickBase()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x28F0);
	}
	float flSimulationTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x68);
	}
	int TeamNum()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xf0);
	}
	Vector OBBMins()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x19C + 0x20);
	}
	Vector OBBMaxs()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x19C + 0x2C);
	}
	//EntIndex
	int Index()
	{
		void* networkable = (void*)(this + 0x8);
		typedef int(__thiscall* OriginalFn)(void*);
		return ((OriginalFn)VMT.GetFunction(networkable, 9))(networkable);
		//return *(int*)(this + 64);
	}

	int GetFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x350);
	}

	Vector GetEyePosition()
	{
		Vector vecViewOffset = *reinterpret_cast<Vector*>((DWORD)this + 0xE8);
		return GetAbsOrigin() + vecViewOffset;
	}

	Vector& GetAbsOrigin()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)VMT.GetFunction(this, 9))(this);
	}

	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)VMT.GetFunction(this, 10))(this);
	}

	void* GetClientClass()
	{
		void* Networkable = (void*)(this + 0x8);
		typedef void* (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)VMT.GetFunction(Networkable, 2))(Networkable);
	}

	bool IsDormant()
	{
		typedef bool(__thiscall* OriginalFn)(void*);
		return ((OriginalFn)VMT.GetFunction(this, 73))(this);
	}

	float MaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x24e4);
	}

	bool isAlive()
	{
		BYTE lifestate = *(BYTE*)((DWORD)this + 0x8F);
		return (lifestate == 0);
	}
	//ValidateModelIndex
	int GetIndex()
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return ((OriginalFn)VMT.GetFunction(this, 70))(this);
	}

	bool SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef bool(__thiscall* OriginalFn)(PVOID, VMatrix*, int, int, float);
		return ((OriginalFn)VMT.GetFunction(pRenderable, 16))(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	const model_t* GetModel()
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef const model_t*(__thiscall* OriginalFn)(PVOID);
		return VMT.getvfunc<OriginalFn>(pRenderable, 9)(pRenderable);
	}

};