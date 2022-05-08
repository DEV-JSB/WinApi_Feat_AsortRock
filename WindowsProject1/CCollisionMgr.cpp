#include "pch.h"
#include "CCollisionMgr.h"

#include"CSceneMgr.h"
#include"CScene.h"

#include"CObject.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}
CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		for (UINT iCol = 0; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if(m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow,(GROUP_TYPE)iCol);
			}
		}
	}

}
// �浹üũ�� �׷��� �޾Ƽ� �浹�� Ȯ���ϴ� �Լ�
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Ȯ���� ���� ���� ����ִ� ������Ʈ ���͵� �� �ϳ��� �޾� �;� �Ѵ�.

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// ���ʿ� �浹ü�� ���� ��쿡 üũ��������� ����ó��
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// ���ʿ� �浹ü�� ���� ��쿡 üũ��������� ����ó��
			// || ���� �׷쳢���� �浹���� �� �ڽŰ��� �浹�� �����ؾ� �Ѵ�.
			if (nullptr == vecRight[i]->GetCollider()
				|| vecLeft[i] == vecRight[i])
				continue;


			// �ǻ�ü�� �����ؼ� �浹�� Ȯ���ϴ� �Լ��� ������.
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[i]->GetCollider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pleftCol, CCollider* _pRightCol)
{
	return true;

}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������ , 
	// �� ū ���� �� (��Ʈ ) �� ���
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow < iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= !(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
	// ????

}



