#include "pch.h"
#include "CCollisionMgr.h"
#include"CCollider.h"
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
	// Row == 행
	// Col == 열
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
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 애초에 충돌체가 없을 경우에 체크하지마라고 예외처리
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 애초에 충돌체가 없을 경우에 체크하지마라고 예외처리
			// || 같은 그룹끼리의 충돌에서 나 자신과의 충돌을 방지해야 한다.
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// 에러 발생지점
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))
				continue;
			// nullptr == vecRight[i] 로 되있었음 ㅎ;
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();



			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 밑의 경우는 두 충돌체 끼리 충돌한 적이 없을 경우 ( 미 등록 상태 )
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				// 최초로 검사를 하는 것 이니 , 이전 프레임의 정보를 충돌하지 않음으로 저장
				iter = m_mapColInfo.find(ID.ID);
				// 이전 프레임 정보 등록
			}


			// 피사체를 전달해서 충돌을 확인하는 함수에 보낸다.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이 내부에 들어 왔던 것 이면 , 현재 충돌 중이다 라는 뜻.
				if (iter->second)
				{
					// 이전에도 충돌하고 있었다.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 둘 중 하나가 죽을 예정이라면 충돌 상태를 벗어나야 한다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);

					}
				}
				else
				{
					// 이전에는 충돌하지 않았다. , 둘 다 삭제 예정이 아닐 경우에만 Enter
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// 현재 충돌하고 있지 않다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);

					iter->second = false;
				}

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pleftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pleftCol->GetFinalPos();
	Vec2 vLeftScale= _pleftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;

	}
	return false;
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



