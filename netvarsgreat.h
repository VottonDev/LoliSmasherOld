#ifndef netvar_h
#define netvar_h
class CNetworkedVariableManager
{
public:

	// stores all tables, and all props inside those
	CNetworkedVariableManager(void);


	// calls GetProp wrapper to get the absolute offset of the prop
	int GetOffset(const char *tableName, const char *propName);


	// calls GetProp wrapper to get prop and sets the proxy of the prop
	bool HookProp(const char *tableName, const char *propName, RecvVarProxyFn function);


private:

	// wrapper so we can use recursion without too much performance loss
	int GetProp(const char *tableName, const char *propName, RecvProp **prop = 0);


	// uses recursion to return a the relative offset to the given prop and sets the prop param
	int GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop = 0);


	RecvTable *GetTable(const char *tableName);


	std::vector<RecvTable*>    m_tables;
};

CNetworkedVariableManager::CNetworkedVariableManager(void)
{
	m_tables.clear();


	ClientClass *clientClass = Interfaces.Client->GetAllClasses();

	if (!clientClass)
	{
		return;
	}


	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pRecvTable;


		m_tables.push_back(recvTable);


		clientClass = clientClass->m_pNext;
	}
}


// calls GetProp wrapper to get the absolute offset of the prop
int CNetworkedVariableManager::GetOffset(const char *tableName, const char *propName) {
	int offset = GetProp(tableName, propName);

	if (!offset) {
		Warning("Failed to find offset for prop: %s from table: %s", propName, tableName);
		return 0;
	}


	return offset;
}


// calls GetProp wrapper to get prop and sets the proxy of the prop
bool CNetworkedVariableManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function) {
	RecvProp *recvProp = 0;
	GetProp(tableName, propName, &recvProp);


	if (!recvProp) {
		Warning("Failed to hook prop: %s from table: %s", propName, tableName);
		return false;
	}


	recvProp->SetProxyFn(function);

	return true;
}


// wrapper so we can use recursion without too much performance loss
int CNetworkedVariableManager::GetProp(const char *tableName, const char *propName, RecvProp **prop) {
	RecvTable *recvTable = GetTable(tableName);

	if (!recvTable) {
		Warning("Failed to find table: %s", tableName);
		return 0;
	}


	int offset = GetProp(recvTable, propName, prop);

	if (!offset) {
		return 0;
	}


	return offset;
}


// uses recursion to return a the relative offset to the given prop and sets the prop param
int CNetworkedVariableManager::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop) {
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i) {
		RecvProp *recvProp = &recvTable->m_pProps[i];


		RecvTable *child = recvProp->GetDataTable();

		if (child
			&& (child->m_nProps > 0)) {
			int tmp = GetProp(child, propName, prop);

			if (tmp) {
				extraOffset += (recvProp->GetOffset() + tmp);
			}
		}


		if (stricmp(recvProp->m_pVarName, propName)) {
			continue;
		}


		if (prop) {
			*prop = recvProp;
		}

		return (recvProp->GetOffset() + extraOffset);
	}

	return extraOffset;
}


RecvTable *CNetworkedVariableManager::GetTable(const char *tableName) {
	if (m_tables.empty()) {
		Warning("Failed to find table: %s (m_tables is empty)", tableName);
		return 0;
	}


	for each (RecvTable *table in m_tables) {
		if (!table) {
			continue;
		}


		if (stricmp(table->m_pNetTableName, tableName) == 0) {
			return table;
		}
	}

	return 0;
}

#endif