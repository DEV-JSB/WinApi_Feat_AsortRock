#include "pch.h"
#include "CScene_Start.h"
#include"CPlayer.h"
#include"CObject.h"
#include"CMonster.h"
#include"CCore.h"

#include"CPathMgr.h"
#include"CTexture.h"

#include"CCollisionMgr.h"


#include"CKeyMgr.h"
#include"CSceneMgr.h"

#include"CCamera.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	///Texture 로딩하기 


	// 오브젝트 추가
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f,384.f));
	pObj->SetScale(Vec2(50.f,50.f));

	CScene::AddObject(pObj, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);


	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	// 플레이어 복사 생성
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	//몬스터 배치
	int iMonsterCount = 2;
	float fMoveDist = 25.f;
	float fObjectScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	float fTerm = (vResolution.x - ((fMoveDist + fObjectScale / 2.f) * 2)) / ((float)iMonsterCount - 1);

	for (int i = 0; i < iMonsterCount; ++i)
	{
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjectScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetScale(Vec2(fObjectScale, fObjectScale));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		CScene::AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);


	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(Vec2(0.1f,0.1f));
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::update()
{
	
	CScene::update();
	if (KEY_TAP_CHECK(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP_CHECK(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}

}
