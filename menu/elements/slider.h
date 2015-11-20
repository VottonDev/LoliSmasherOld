class LSlider : public LBaseObject
{
protected:
	float Value, PaintValue, MinVar, MaxVar;
	float* Var = &Value;

	bool isDragging = false;
	const char* Text = "Slider";
public:
	using LBaseObject::LBaseObject;
	LSlider();
	virtual void Think();
	virtual void Paint();

	void SetRange(float min, float max) { MinVar = min; MaxVar = max; }
	void SetDefault(float value) { Value = value; PaintValue = clamp((Value / MaxVar) * w, 0, w); }

	void SetText(const char* text) { Text = text; }
	const char* GetText() { return Text; }

	void SetVar(float* VAR) { Var = VAR; }
	float GetVar() { return *Var; }
};

LSlider::LSlider()
{
	w = 200;
	h = 20;
}

void LSlider::Paint()
{

	int X, Y;
	GetPos(&X, &Y);

	Visuals.DrawRect(X, Y, w, h, Color(0, 0, 0, 100));
	Visuals.DrawRect(X, Y, PaintValue, h, LMenuFG);

	if (Hovering)
		Visuals.DrawRect(X, Y, PaintValue, h, Color(255, 255, 255, 20));

	int W,H;
	Visuals.GetTextSize( Visuals.MenuFont, "00", W, H ); // Surely there's a better way to do this...

	Visuals.DrawStringC(Visuals.SmallMenuFont, X, Y - 15, 255, 255, 255, 255, "%s", Text);
	Visuals.DrawStringC(Visuals.SmallMenuFont, X + w - W, Y - 15, 255, 255, 255, 255, "%g", Value);

}

void LSlider::Think()
{

	if (!isDragging && InputManager.IsMouseClicked() && Hovering)
		isDragging = true;

	if (!InputManager.IsMouseClicked())
		isDragging = false;

	if (!isDragging)
		return;

	int MouseX, _;
	InputManager.GetMousePos(&MouseX, &_);

	int X;
	GetPos(&X, &_);

	float diff = (MouseX - X);

	PaintValue = clamp(diff, 0, w);

	float perc = (diff / w);
	float range = MaxVar - MinVar;
	range = range * perc;

	Value = clamp(roundf(MinVar + range), MinVar, MaxVar);
	*Var = Value;

}