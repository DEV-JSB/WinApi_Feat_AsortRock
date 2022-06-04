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
	///Texture �ε��ϱ� 


	// ������Ʈ �߰�
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f,384.f));
	pObj->SetScale(Vec2(50.f,50.f));

	CScene::AddObject(pObj, GROUP_TYPE::PLAYER);


	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	// �÷��̾� ���� ����
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	//���� ��ġ
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

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);


	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
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
}
