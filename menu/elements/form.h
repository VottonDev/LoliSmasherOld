class LForm :  public LBaseObject
{
protected:
	int Padding = 30;
	std::vector<LBaseObject*> ObjectList;
public:
	void Paint();
	void AddItem( LBaseObject* );
};

void LForm::Paint()
{
	int X, Y;
	GetPos(&X,&Y);
	Interfaces.Surface->DrawSetColor( LMenuFG );
	Interfaces.Surface->DrawOutlinedRect( X, Y, X + w, Y + h );
}

void LForm::AddItem( LBaseObject* Item )
{
	Item->SetParent(this);
	int Height = 10; 
	Height += ObjectList.size()*Padding;
	Item->SetPos(10, Height);
	ObjectList.push_back(Item);
}