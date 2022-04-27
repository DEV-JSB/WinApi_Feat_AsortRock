#include "pch.h"
#include "CMonster.h"
#include"CTimeMgr.h"

CMonster::CMonster()
	: m_fSpeed(100.f)
	, m_vCenterPos{ Vec2(0.f,0.f) }
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	if (0.f < fDist)
	{
		// ���� ���� �� �Ѿ �Ÿ� ����
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}


CMonster::~CMonster()
{
	
}