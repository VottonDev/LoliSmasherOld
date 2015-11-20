class CVariable
{
protected:
	const char* Name;
	int* Value;
public:
	CVariable( const char* NewName, int* NewValue ) { Name = NewName; Value = NewValue; }
	const char* GetName() { return Name; };
	int GetValue() { return *Value; };
	void SetValue(int Val) { *Value = Val; };
	int* GetPointer() { return Value; };
};

class CVariables
{
protected:
	std::vector<CVariable*> VariableList;
public:
	std::vector<CVariable*> GetVariables() { return VariableList; };
	CVariable* GetVar( const char* );
	CVariable* CreateVar( const char*, int* );
}; CVariables Variables;

CVariable* CVariables::GetVar( const char* Name )
{
	
	CVariable* Var = nullptr;
	for ( CVariable* Variable : VariableList )
	{
		if ( !strcmp( Name, Variable->GetName() ) )
		{
			Var = Variable;
			break;
		}
	}

	if ( Var == nullptr )
	{
		MessageBoxEx( NULL, "ok", NULL, NULL, NULL );
	}

	return Var;

}

CVariable* CVariables::CreateVar( const char* Name, int* Value = new int )
{
	CVariable* NewVariable = new CVariable( Name, Value );
	VariableList.push_back( NewVariable );
	return NewVariable;
}