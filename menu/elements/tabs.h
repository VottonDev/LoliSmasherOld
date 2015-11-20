class LTab : public LBaseObject
{
protected:
	int Index = 0;
	bool CurTab = false;
	const char* Name = "Tab";
public:
	using LBaseObject::LBaseObject;
	LTab();
	LTab(int);
	virtual void Paint();
	virtual void MouseClick();

	void SetName(const char* name) { Name = name; }
	const char* GetName() { return Name; }

	void SetIndex(int index) { Index = index; }
	int GetIndex() { return Index; }

	void SetCurTab(bool curtab) { CurTab = curtab; }
	bool GetCurTab() { return CurTab; }
};

LTab::LTab()
{
	w = 60;
	h = 20;
}

LTab::LTab(int index)
{
	w = 60;
	h = 20;

	Index = index;
}

void LTab::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Interfaces.Surface->DrawSetColor(LMenuFG);

	Interfaces.Surface->DrawLine(X, Y, X, Y + h);
	Interfaces.Surface->DrawLine(X, Y, X + w, Y);
	Interfaces.Surface->DrawLine(X + w, Y, X + w, Y + h);

	if (Hovering && !CurTab)
		Visuals.DrawRect(X, Y, w, h, Color(255, 255, 255, 10));

	int TextX, TextY;
	Visuals.GetTextSize(Visuals.MenuFont, Name, TextX, TextY);

	TextX = X + (w * 0.5) - (TextX * 0.5);
	TextY = Y + (h * 0.5) - (TextY * 0.5);

	Visuals.DrawStringC(Visuals.MenuFont, TextX, TextY + 1, 255, 255, 255, 255, "%s", Name);

}

//

class LTabPanel : public LBaseObject
{
protected:
	std::vector<LTab*> Tabs;
	std::vector<LBaseObject*> Panels;
	int CurTab = 0;

public:
	using LBaseObject::LBaseObject;
	virtual void Paint();

	LBaseObject* AddTab(const char*);
	void SetCurrentTab(int);
	void SetCurrentTab(const char*);

	LBaseObject* GetTab(const char*);
	LBaseObject* GetTab(int);
};

void LTab::MouseClick()
{
	LTabPanel* par = (LTabPanel*)Parent;
	par->SetCurrentTab(Index);
}

void LTabPanel::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Y = Y + 20;

	int H = h - 20;

	Interfaces.Surface->DrawSetColor(LMenuFG);

	Interfaces.Surface->DrawLine(X, Y, X, Y + H);
	Interfaces.Surface->DrawLine(X, Y + H, X + w, Y + H);
	Interfaces.Surface->DrawLine(X + w, Y, X + w, Y + H);

	if (Tabs.size() <= 0) 
		return;

	int TabX, TabY;
	Tabs[CurTab]->GetPos(&TabX, &TabY);

	Interfaces.Surface->DrawLine(X, Y, TabX, Y);
	Interfaces.Surface->DrawLine(TabX + 60, Y, X + w, Y);

}

LBaseObject* LTabPanel::AddTab(const char* name)
{

	LTab* Tab = new LTab(Tabs.size());
	Tab->SetParent(this);
	Tab->SetPos(65 * Tabs.size(), 0);
	Tab->SetName(name);

	Tabs.push_back(Tab);

	LBaseObject* Panel = new LBaseObject();
	Panel->SetParent(this);
	Panel->SetPos(0, 20);
	Panel->SetSize(w, h - 20);
	Panel->SetVisible(false);

	Panels.push_back(Panel);

	SetCurrentTab(Tabs.size() - 1);

	return Panel;

}

void LTabPanel::SetCurrentTab(int index)
{

	if (CurTab == index)
		return;

	CurTab = index;

	for (LTab* Tab : Tabs)
	{
		Tab->SetCurTab(Tab->GetIndex() == index);
	}

	for (LBaseObject* Panel : Panels)
	{
		Panel->SetVisible(false);
	}

	Panels[index]->SetVisible(true);

}

void LTabPanel::SetCurrentTab(const char* name)
{

	int index = 0;

	for (LTab* Tab : Tabs)
	{
		if (strcmp(Tab->GetName(), name) == 0)
		{
			index = Tab->GetIndex();
			break;
		}
	}

	if (CurTab == index)
		return;

	CurTab = index;

	for (LTab* Tab : Tabs)
	{
		Tab->SetCurTab(Tab->GetIndex() == index);
	}

	for (LBaseObject* Panel : Panels)
	{
		Panel->SetVisible(false);
	}

	Panels[index]->SetVisible(true);

}

LBaseObject* LTabPanel::GetTab(const char* name)
{

	for (LTab* Tab : Tabs)
	{
		if (strcmp(Tab->GetName(), name) == 0)
			return Panels[Tab->GetIndex()];
	}

	return Panels[0];

}

LBaseObject* LTabPanel::GetTab(int index)
{

	return Panels[index];

}