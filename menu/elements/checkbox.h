class LCheckBox : public LBaseObject
{
protected:
	int* Var = 0;

	const char* Text = "Checkbox";
public:
	using LBaseObject::LBaseObject;
	LCheckBox();
	virtual void Paint();
	virtual void MouseClick();

	void SetText(const char* text) { Text = text; }
	const char* GetText() { return Text; }

	void SetVar(int* VAR) { Var = VAR; *Var = 0; } // Since VAR has no value it took multiple clicks for anything to happen, so I initialize it as disabled (0)
	bool GetVar() { return *Var; }
};

LCheckBox::LCheckBox()
{
	w = 20;
	h = 20;
}

void LCheckBox::Paint()
{
	
	int X, Y;
	GetPos(&X, &Y);

	Interfaces.Surface->DrawSetColor(LMenuFG);

	Visuals.DrawOutlinedRect(X, Y, w, h, LMenuFG);
	Interfaces.Surface->DrawOutlinedRect(X, Y, w, h);

	if (*Var == 1) // In binary 1 is on, not 0 right?
		Interfaces.Surface->DrawFilledRect(X + 2, Y + 2, X + w - 2, Y + h - 2);

	Visuals.DrawStringC(Visuals.MenuFont, X + w + 10, Y + (h * 0.5) - 10, 255, 255, 255, 255, "%s", Text);
	
}

void LCheckBox::MouseClick()
{
	if ( *Var == 1 )
	{
		*Var = 0;
	}
	else
	{
		*Var = 1;
	}
}