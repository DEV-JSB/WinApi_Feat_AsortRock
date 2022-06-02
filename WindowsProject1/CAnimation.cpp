#include "pch.h"
#include "CAnimation.h"
#include"CAnimator.h"
#include"CTexture.h"
#include"CObject.h"
#include"CTimeMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	,m_fAccTime(0.f)
	,m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;
	m_fAccTime += fDT;
	// 시간을 매 프레임 마다 계속 누적 시킨다.

	// 현재 프레임에서 머물러야 할 시간을 넘어버린다면 다음 프레임 전환
	if ( m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0;
			return;
		}
		//m_fAccTime = 0.f;
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset;

	// 2번째 인자값 좌상단 좌표는 플레이어 중심에 한 프레임의 애니메이션 크기의 절반 만큼 빼서 계산한 값 이다.
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
			, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
				, m_pTex->GetDC()
				, (int)(m_vecFrm[m_iCurFrm].vLT.x)
				, (int)(m_vecFrm[m_iCurFrm].vLT.y)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
				, RGB(255, 0, 255)
				);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _SliceSize, Vec2 _vStep,
						float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _SliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}
