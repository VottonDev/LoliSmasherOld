class CConsole
{
public:
	void Initialize()
	{
		AllocConsole();

		HWND hwnd = GetConsoleWindow();
		if (!hwnd) return;

		HMENU hMenu = GetSystemMenu(hwnd, FALSE);
		if (hMenu) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

		SetConsoleTitle("[lolismasher]: Console");
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);

	}

}; CConsole Console;