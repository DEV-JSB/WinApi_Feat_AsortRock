#pragma once

class CScene;


class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene* m_pCurScene;						// ���� ��

public:
	void Init();
	void update();
	void render(HDC _hdc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	// �̺�Ʈ ó�� �Ŀ� Change �� �ؾ� ������ , private ����.
	//
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

