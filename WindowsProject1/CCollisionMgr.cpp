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
	// Row == ��
	// Col == ��
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
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// ���ʿ� �浹ü�� ���� ��쿡 üũ��������� ����ó��
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// ���ʿ� �浹ü�� ���� ��쿡 üũ��������� ����ó��
			// || ���� �׷쳢���� �浹���� �� �ڽŰ��� �浹�� �����ؾ� �Ѵ�.
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ���� �߻�����
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))
				continue;
			// nullptr == vecRight[i] �� ���־��� ��;
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();



			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// ���� ���� �� �浹ü ���� �浹�� ���� ���� ��� ( �� ��� ���� )
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				// ���ʷ� �˻縦 �ϴ� �� �̴� , ���� �������� ������ �浹���� �������� ����
				iter = m_mapColInfo.find(ID.ID);
				// ���� ������ ���� ���
			}


			// �ǻ�ü�� �����ؼ� �浹�� Ȯ���ϴ� �Լ��� ������.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �� ���ο� ��� �Դ� �� �̸� , ���� �浹 ���̴� ��� ��.
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �� �� �ϳ��� ���� �����̶�� �浹 ���¸� ����� �Ѵ�.
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
					// �������� �浹���� �ʾҴ�. , �� �� ���� ������ �ƴ� ��쿡�� Enter
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
				// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
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



