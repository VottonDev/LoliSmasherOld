
GMODCUserCmd *__stdcall hkGetUserCmd(int sqnum)
{
	static GMODCUserCmd* pCommands = *(GMODCUserCmd **)((DWORD)Interfaces.Input + 0xC4);
	GMODCUserCmd *pCmd = &pCommands[sqnum % 90];
	if (pCmd)
	{
		/*static int randomint = 0;
		static int hash = MD5_PseudoRandom(142) & 255;
		pCmd->random_seed = MD5_PseudoRandom(pCmd->command_number = randomint++);
		int brute = 0;
		for (int i = randomint + 1; !brute; i++)
		{
			if ((MD5_PseudoRandom(i) & 255) == hash)
			{
				brute = i;
			}
		}
		pCmd->random_seed = MD5_PseudoRandom(pCmd->command_number = randomint = brute) & 0x7FFFFFFF;*/
		pCmd->command_number = 142;
		pCmd->random_seed = MD5_PseudoRandom(142) & 0x7FFFFFFF;
	}
	return pCmd;
}
PaintTraverseFn orgPaintTraverse;
class CHooks
{
public:

	void GetHooks()
	{
		CVMTHookManager* CHLClient = new CVMTHookManager(Interfaces.Client);
		orgCreateMove = (CreateMoveFn)CHLClient->HookFunction(21, hkCreateMove);
		CHLClient->HookTable(true);

		CVMTHookManager* PanelHook = new CVMTHookManager(Interfaces.Panel);
		orgPaintTraverse = (PaintTraverseFn)PanelHook->HookFunction(41, hkPaintTraverse);
		PanelHook->HookTable(true);

		CVMTHookManager* InputHk = new CVMTHookManager(Interfaces.Input);
		InputHk->HookFunction(8, hkGetUserCmd);
		InputHk->HookTable(true);
	}
}; CHooks Hooks;
CreateMoveFn orgCreateMove;