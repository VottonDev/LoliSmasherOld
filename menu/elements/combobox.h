class LOption : public LBaseObject
{
protected:
	const char* Text;
	int* Value;
public:
	void Paint();
	void MouseClick();

	void SetText(const char* text) { Text = text; }
	void SetValue(int* value) { Value = value; }
};

void LOption::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Visuals.DrawRect(X, Y, w, h, Color(0, 0, 0, 100));

	if (Hovering)
		Visuals.DrawRect(X, Y, w, h, Color(255, 255, 255, 5));

	Visuals.DrawOutlinedRect(X, Y, w, h, LMenuFG);
	Visuals.DrawStringC(Visuals.MediumMenuFont, X + 4, Y + 2, 255, 255, 255, 255, "%s", Text);

}

//

class LComboBox : public LBaseObject
{
protected:
	bool Collapsed = false;
	int Value = 0;
	int* Var = &Value;
	const char* Text = "ComboBox";

	std::vector <LOption*> OptionList;
public:
	LComboBox();
	void Paint();
	void MouseClick();

	LOption* AddOption(const char* text, int* value);
	void SetText(const char* text) { Text = text; }
	const char* GetText() { return Text; }

	void SetValue(int* value) { Value = *value; Var = value; }
	int GetValue() { return Value; }

	void SetVar(int* var) { Var = var; }
	int GetVar() { return *Var; }
	int* GetVarPointer() { return Var; }
};

LComboBox::LComboBox()
{
	w = 100;
	h = 20;

	this->SetChildrenPrivate(true);
}

void LOption::MouseClick()
{

	LComboBox* par = (LComboBox*)Parent;
	par->SetText(Text);
	par->SetValue(Value);

	par->MouseClick();

}

void LComboBox::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Visuals.DrawRect(X, Y, w, h, Color(0, 0, 0, 100));

	if (Hovering)
		Visuals.DrawRect(X, Y, w - 20, h, Color(255, 255, 255, 5));

	Interfaces.Surface->DrawSetColor(LMenuFG);
	Interfaces.Surface->DrawOutlinedRect(X, Y, X + w, Y + h);

	Visuals.DrawStringC(Visuals.MediumMenuFont, X + 4, Y + 2, 255, 255, 255, 255, "%s", Text);

	int bx = X + w - h;
	int hbx = h * 0.5;

	Interfaces.Surface->DrawLine(bx, Y, bx, Y + h - 1);
	Interfaces.Surface->DrawLine(bx + 6, Y + 8, bx + 10, Y + 12);
	Interfaces.Surface->DrawLine(bx + 10, Y + 12, bx + 14, Y + 8);

	if (Collapsed)
	{
		Interfaces.Surface->DrawFilledRect(bx, Y, bx + 20, Y + 20);

		Interfaces.Surface->DrawSetColor(Color(0, 0, 0, 255));
		Interfaces.Surface->DrawLine(bx + hbx - 4, Y + hbx - 2, bx + 10, Y + hbx + 2);
		Interfaces.Surface->DrawLine(bx + hbx, Y + 12, bx + hbx + 4, Y + hbx - 2);
	}
	else 
	{
		Interfaces.Surface->DrawLine(bx, Y, bx, Y + h - 1);
		Interfaces.Surface->DrawLine(bx + hbx - 4, Y + hbx - 2, bx + 10, Y + hbx + 2);
		Interfaces.Surface->DrawLine(bx + hbx, Y + 12, bx + hbx + 4, Y + hbx - 2);
	}

}

LOption* LComboBox::AddOption(const char* text, int* value)
{

	LOption* Option = new LOption();
	Option->SetParent(this);
	Option->SetPos(0, h - 1 + ((h-1) * OptionList.size()));
	Option->SetSize(w, h);
	Option->SetText(text);
	Option->SetValue(value);

	OptionList.push_back(Option);

	return Option;

}

void LComboBox::MouseClick()
{

	Collapsed = !Collapsed;

	for (LOption* Option : OptionList)
	{
		Option->SetVisible(Collapsed);
	}

}