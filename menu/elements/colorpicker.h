class LColorPicker : public LBaseObject
{
protected:
	LSlider* RedSlider, *GreenSlider, *BlueSlider, *AlphaSlider;
	float Red, Green, Blue, Alpha;
	Color* Col;
	const char* Text = "Color Picker";

public:
	using LBaseObject::LBaseObject;
	LColorPicker();
	virtual void Paint();
	virtual void Think();

	void SetColor(Color);
	void SetColor(int, int, int, int);
	void SetText(const char* text) { Text = text; }
	void SetVar(Color* col) { Col = col; }

};

LColorPicker::LColorPicker()
{
	w = 355;
	h = 100;

	RedSlider = new LSlider();
	RedSlider->SetParent(this);
	RedSlider->SetPos(100, 15);
	RedSlider->SetSize(255, 10);
	RedSlider->SetRange(0, 255);
	RedSlider->SetText("Red");
	RedSlider->SetVar(&Red);

	GreenSlider = new LSlider();
	GreenSlider->SetParent(this);
	GreenSlider->SetPos(100, 40);
	GreenSlider->SetSize(255, 10);
	GreenSlider->SetRange(0, 255);
	GreenSlider->SetText("Green");
	GreenSlider->SetVar(&Green);

	BlueSlider = new LSlider();
	BlueSlider->SetParent(this);
	BlueSlider->SetPos(100, 65);
	BlueSlider->SetSize(255, 10);
	BlueSlider->SetRange(0, 255);
	BlueSlider->SetText("Blue");
	BlueSlider->SetVar(&Blue);

	AlphaSlider = new LSlider();
	AlphaSlider->SetParent(this);
	AlphaSlider->SetPos(100, 90);
	AlphaSlider->SetSize(255, 10);
	AlphaSlider->SetRange(0, 255);
	AlphaSlider->SetText("Alpha");
	AlphaSlider->SetVar(&Alpha);

}

void LColorPicker::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Visuals.DrawRect(X, Y + 20, 80, 80, *Col);

	Visuals.DrawStringC(Visuals.SmallMenuFont, X, Y, 255, 255, 255, 255, "%s", Text);

}

void LColorPicker::Think()
{

	Color col = Color(Red, Green, Blue, Alpha);

	*Col = col;

}

void LColorPicker::SetColor(Color col)
{

	int r, g, b, a;
	col.GetColor(r, g, b, a);

	Red = r;
	RedSlider->SetDefault(r);

	Green = g;
	GreenSlider->SetDefault(g);

	Blue = b;
	BlueSlider->SetDefault(b);

	Alpha = a;
	AlphaSlider->SetDefault(a);

	*Col = col;

}

void LColorPicker::SetColor(int r, int g, int b, int a)
{

	Red = r;
	RedSlider->SetDefault(r);

	Green = g;
	GreenSlider->SetDefault(g);

	Blue = b;
	BlueSlider->SetDefault(b);

	Alpha = a;
	AlphaSlider->SetDefault(a);

	*Col = Color(r, g, b, a);

}