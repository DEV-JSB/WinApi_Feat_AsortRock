#pragma once

class CScene;


class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	CScene* m_pCurScene;						// 현재 씬

public:
	void Init();
	void update();
	void render(HDC _hdc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	// 이벤트 처리 후에 Change 를 해야 함으로 , private 선언.
	//
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

