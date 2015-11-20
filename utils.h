class CUtils
{
public:
	inline CBaseEntityNew* LocalPlayer()
	{
		return Interfaces.ClientEntList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
	}
}; extern CUtils Utilities;