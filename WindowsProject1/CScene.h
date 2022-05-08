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

	virtual void Enter() = 0; // �ش� ���� ���Խ� ȣ��
	virtual void Exit() = 0;  // �ش� ���� Ż��� ȣ��


	void update();
	void finalupdate();
	void render(HDC _hdc);





public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrvecObj[(UINT)_eType].push_back(_pObj);
	}

	// ���� ����ִ� �׷��� ���� ������ �϶�� �����ִ� �Լ�
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrvecObj[(UINT)_eType];
	}

public:
	CScene();
	virtual ~CScene();

};

