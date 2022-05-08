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
// 충돌체크된 그룹을 받아서 충돌을 확인하는 함수
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 확인을 위해 씬이 들고있는 오브젝트 벡터들 중 하나를 받아 와야 한다.

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 애초에 충돌체가 없을 경우에 체크하지마라고 예외처리
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 애초에 충돌체가 없을 경우에 체크하지마라고 예외처리
			// || 같은 그룹끼리의 충돌에서 나 자신과의 충돌을 방지해야 한다.
			if (nullptr == vecRight[i]->GetCollider()
				|| vecLeft[i] == vecRight[i])
				continue;


			// 피사체를 전달해서 충돌을 확인하는 함수에 보낸다.
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
	// 더 작은 값의 그룹 타입을 행으로 , 
	// 더 큰 값을 열 (비트 ) 로 사용
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



