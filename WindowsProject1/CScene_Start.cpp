#include "pch.h"
#include "CScene_Start.h"
#include"CPlayer.h"
#include"CObject.h"
#include"CMonster.h"
#include"CCore.h"

#include"CPathMgr.h"
#include"CTexture.h"

#include"CCollisionMgr.h"

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
	pObj->SetScale(Vec2(100.f,100.f));

	CScene::AddObject(pObj, GROUP_TYPE::PLAYER);


	//���� ��ġ
	int iMonsterCount = 13;
	float fMoveDist = 25.f;
	float fObjectScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	float fTerm = (vResolution.x - ((fMoveDist + fObjectScale / 2.f) * 2)) / ((float)iMonsterCount - 1);

	for (int i = 0; i < iMonsterCount; ++i)
	{
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjectScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetScale(Vec2(fObjectScale, fObjectScale));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		CScene::AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
}
