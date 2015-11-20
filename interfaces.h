class CInterfaces
{
public:
	CEngine *Engine;
	IBaseClientDLL *Client;
	CInput *Input;
	CClientEntityListNew *ClientEntList;
	IVModelInfo *ModelInfo;
	IPanel* Panel;
	ISurface* Surface;
	IEngineTrace *Trace;
	CGlobalVarsBase* Globals;
	IGameEventManager2 *GameEventManager;
	ICvarNew* Cvar;
	IPredictionNew *Prediction;
	IGameMovement *Move;
	void GetInterfaces()
	{
		CreateInterfaceFn EngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
		Engine = (CEngine*)GetPointer("engine.dll", "VEngineClient");
		Client = (IBaseClientDLL*)GetPointer("client.dll", "VClient");
		ClientEntList = (CClientEntityListNew*)GetPointer("client.dll", "VClientEntityList");
		ModelInfo = (IVModelInfo*)GetPointer("engine.dll", "VModelInfoClient");
		Trace = (IEngineTrace*)GetPointer("engine.dll", "EngineTraceClient");
		GameEventManager = (IGameEventManager2*)EngineFactory("GAMEEVENTSMANAGER002",0);
		Cvar = (ICvarNew*)GetPointer("vstdlib.dll", "VEngineCvar");
		if (!Cvar)
			::MessageBox(0, "Broke", 0, 0);
		Prediction = (IPredictionNew*)GetPointer("client.dll", "VClientPrediction");
		Move = (IGameMovement*)GetPointer("client.dll", "GameMovement");
		Panel = (IPanel*)GetPointer("vgui2.dll", "VGUI_Panel");
		Surface = (ISurface*)GetPointer("vguimatsurface", "VGUI_Surface");
		Input = **(CInput***)((*(DWORD**)Client)[14] + 0x2);
		//http://www.unknowncheats.me/forum/960874-post340.html
		// gmod 2nd push instead of first

		Globals = (CGlobalVarsBase*)((DWORD)GetModuleHandle("engine.dll") + 0x3AD5A8);
	}

	void* GetPointer(const char* Module, const char* InterfaceName)
	{
		void* Interface = NULL;
		char PossibleInterfaceName[1024];

		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");
		for (int i = 1; i < 100; i++)
		{
			sprintf(PossibleInterfaceName, "%s0%i", InterfaceName, i);
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				std::cout << PossibleInterfaceName << " Found!\n";
				break;
			}
			sprintf(PossibleInterfaceName, "%s00%i", InterfaceName, i);
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				std::cout << PossibleInterfaceName << " Found!\n";
				break;
			}
		}

		return Interface;
	}
}; CInterfaces Interfaces;