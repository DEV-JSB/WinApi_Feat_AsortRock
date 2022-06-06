#include "pch.h"
#include "CCamera.h"
#include"CObject.h"
#include"CCore.h"

#include"CTimeMgr.h"
#include"CKeyMgr.h"


CCamera::CCamera()
	:m_pTargetObj(nullptr)
{

}
CCamera::~CCamera()
{

}



void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD_CHECK(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD_CHECK(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD_CHECK(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD_CHECK(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::CalDiff()
{
	// 이전 LookAt과 현재 Look 의 차이 값을 보정해서 현재의 LookAt 을 구한다.
	Vec2 vLookDir = m_vLookAt -	m_vPrevLookAt;

	m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * 500.f * fDT;



	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;


	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
