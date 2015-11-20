class IPredictionNew
{
public:
	void SetupMove(void* ply, void* cmd, void* mhelp, void* data)
	{
		typedef void(__thiscall* fn)(void*, void*, void*, void*, void*);
		VMT.getvfunc<fn>(this, 18)(this, ply, cmd, mhelp, data);
	}
	void FinishMove(void*ply, void*cmd, void*data)
	{

		typedef void(__thiscall* fn)(void*, void*, void*, void*);
		VMT.getvfunc<fn>(this, 19)(this, ply, cmd, data);
	}
};
class CEngine
{
public:

	void GetScreenSize(int& Width, int& Height)
	{
		typedef void(__thiscall* Fn)(void*, int&, int&);
		return ((Fn)VMT.GetFunction(this, 5))(this, Width, Height);
	}
	INetChannelInfo *GetNetChannelInfo()
	{
		//78
		typedef INetChannelInfo*(__thiscall* fn)(void*);
		return ((fn)VMT.GetFunction(this, 72))(this);
	}
	bool GetPlayerInfo(int Index, player_info_t* PlayerInfo)
	{
		typedef bool(__thiscall* Fn)(void*, int, player_info_t*);
		return ((Fn)VMT.GetFunction(this, 8))(this, Index, PlayerInfo);
	}
	int GetPlayerForUserID(int i)
	{
		typedef int(__thiscall* fn)(void*, int);
		return VMT.getvfunc<fn>(this, 9)(this, i);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall* Fn)(void*);
		return ((Fn)VMT.GetFunction(this, 12))(this);
	}

	void ClientCmd(const char* Command)
	{
		typedef void(__thiscall* Fn)(void*, const char*);
		return ((Fn)VMT.GetFunction(this, 102))(this, Command);
	}

	void SetViewAngles(Vector& Angles)
	{
		typedef void(__thiscall* Fn)(void*, Vector&);
		return ((Fn)VMT.GetFunction(this, 20))(this, Angles);
	}

	void GetViewAngles(Vector& angle)
	{
		typedef void(__thiscall* Fn)(void*, Vector&);
		return ((Fn)VMT.GetFunction(this, 19))(this, angle);
	}

	VMatrix& WorldToScreenMatrix()
	{
		typedef VMatrix& (__thiscall* Fn)(void*);
		return ((Fn)VMT.GetFunction(this, 36))(this);

	}

};