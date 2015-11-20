class CClientEntityListNew
{
public:

	CBaseEntityNew* GetClientEntity(int Index)
	{
		typedef CBaseEntityNew*(__thiscall* Fn)(void*, int);
		return ((Fn)VMT.GetFunction(this, 3))(this, Index);
	}

	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* Fn)(void*);
		return ((Fn)VMT.GetFunction(this, 6))(this);
	}

	CBaseEntityNew* GetClientEntityFromHandle(HANDLE Handle)
	{
		typedef CBaseEntityNew*(__thiscall* Fn)(void*, HANDLE);
		return ((Fn)VMT.GetFunction(this, 4))(this, Handle);
	}

};