class ICvarNew
{
public:
	ConVar *FindVar(char const* name)
	{
		typedef ConVar*(__thiscall* fn)(void*, const char*);
		return VMT.getvfunc<fn>(this, 12)(this, name);
	}
};