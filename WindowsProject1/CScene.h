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

	virtual void Enter() = 0; // 해당 씬에 진입시 호출
	virtual void Exit() = 0;  // 해당 씬에 탈출시 호출


	void update();
	void finalupdate();
	void render(HDC _hdc);





public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrvecObj[(UINT)_eType].push_back(_pObj);
	}

	// 씬에 담겨있는 그룹을 그저 참조만 하라고 보내주는 함수
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrvecObj[(UINT)_eType];
	}

public:
	CScene();
	virtual ~CScene();

};

