class CMisc
{
public:

	void SpeedHack(void* CL_Move, int Factor)
	{

		if (!GetAsyncKeyState(VK_LSHIFT))
			return;

		DWORD* ReturnAddress = (DWORD*)(*(DWORD*)CL_Move + 0x4);
		if (Speed > 1)
		{
			Speed -= 1;
			*ReturnAddress -= 0x5;
		}
		else
		{
			Speed = Factor;
		}
	}

private:
	int Speed;
}; CMisc Misc;