#include "pch.h"
#include "CSceneMgr.h"

#include"CScene_Start.h"
#include"CScene_Tool.h"
#include"CSceneMgr.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{
}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::Init()
{
	//SCene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene"); \

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;




	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TOOL];
	m_pCurScene->Enter();

}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _hdc)
{
	m_pCurScene->render(_hdc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}

