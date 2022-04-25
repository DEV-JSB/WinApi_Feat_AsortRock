#pragma once

class CObject;

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 생성
	vector<CObject*>	m_arrvecObj[(UINT)GROUP_TYPE::END]; 
	wstring				m_strName; // 씬 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

};

