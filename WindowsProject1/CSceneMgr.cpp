#include "pch.h"
#include "CSceneMgr.h"

#include"CScene_Start.h"

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
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;

	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

}
