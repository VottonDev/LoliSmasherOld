class LBaseObject
{
protected:
	int x, y, w, h;
	bool Hovering = false;
	bool Clicked = false;
	bool Visible = true;
	bool ChildrenPrivate = false;

	LBaseObject* Parent = nullptr;
	std::vector<LBaseObject*> Children;

	void SortChildren();
	bool ClickedParent();
	bool ClickedChild();
public:
	LBaseObject();
	virtual void Tick();
	virtual void Think();
	virtual void Paint();
	virtual void MouseClick() {}
	virtual void MouseRelease() {}

	void SetPos(int X, int Y) { x = X; y = Y; }
	void GetPos(int*, int*);

	void SetSize(int W, int H) { w = W; h = H; }
	void GetSize(int* W, int* H) { *W = w; *H = h; }

	void SetVisible(bool, bool);
	bool GetVisible() { return Visible; }

	void SetChildrenPrivate(bool Private) { ChildrenPrivate = Private; };

	void SetParent(LBaseObject*);
	LBaseObject* GetParent() { return Parent; };

	std::vector<LBaseObject*> GetChildren() { return Children; };

	bool IsHovered() { return Hovering; }
	bool IsClicked() { return Clicked; }

};

LBaseObject::LBaseObject()
{
	x = 0;
	y = 0;

	w = 50;
	h = 50;

	PanelObjects.push_back( this );
}

void LBaseObject::SortChildren()
{
	if ( this->Children.size() == 0 )
		return;
	for( LBaseObject* Child : Children )
	{
		InputManager.Focus( Child );
		Child->SortChildren();
	}
}


bool LBaseObject::ClickedParent()
{
	if ( Parent != nullptr )
	{
		if ( Parent == InputManager.ClickedPanel )
			return true;
		if ( Parent->ClickedParent() )
			return true;
	}
	return false;
}

bool LBaseObject::ClickedChild()
{
	for( LBaseObject* Child : this->GetChildren() )
	{
		if ( InputManager.ClickedPanel == Child )
			return true;
		if ( Child->ClickedChild() )
			return true;
	}
	return false;
}

void LBaseObject::Tick()
{

	if ( !InputManager.CanClick() && InputManager.ClickedPanel != this && Parent != InputManager.ClickedPanel && !ClickedParent() && !ClickedChild() )
		return;

	int MouseX, MouseY;
	InputManager.GetMousePos(&MouseX, &MouseY);

	int X, Y;
	GetPos(&X, &Y);

	Hovering = false;
	if (MouseX > X && MouseX < X + w && MouseY > Y && MouseY < Y + h)
		Hovering = true;

	if (InputManager.IsMouseClicked() && Hovering)
	{
		if (!Clicked)
		{
			MouseClick();
			Clicked = true;

			if ( Parent == nullptr )
			{
				InputManager.Focus(this);
				SortChildren();
				InputManager.ClickedPanel = this;
			}
		}
	}
	else if (Clicked)
	{
		MouseRelease();
		Clicked = false;
		if ( this == InputManager.ClickedPanel )
			InputManager.ClickedPanel = nullptr;
	}

	Think();

}

void LBaseObject::Paint()
{

}

void LBaseObject::Think()
{

}

void LBaseObject::SetParent(LBaseObject* parent)
{

	Parent = parent;
	Visible = Parent->Visible;

	Parent->Children.push_back(this);

}

void LBaseObject::SetVisible(bool visible, bool fromParent = false)
{

	Visible = visible;

	if (fromParent && ChildrenPrivate)
		return;

	for (LBaseObject* Panel : Children)
	{
		Panel->SetVisible(visible, true);
	}

}

void LBaseObject::GetPos(int* X, int* Y)
{

	if (Parent == nullptr)
	{
		*X = x;
		*Y = y;
	}
	else
	{
		int ParentX;
		int ParentY;
		Parent->GetPos( &ParentX, &ParentY );
		*X = x + ParentX;
		*Y = y + ParentY;
	}

}