#pragma once

class CObject;

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<CObject*>	m_arrvecObj[(UINT)GROUP_TYPE::END]; 
	wstring				m_strName; // �� �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

};

