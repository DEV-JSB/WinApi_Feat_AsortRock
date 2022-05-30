#include "pch.h"
#include "CAnimation.h"
#include"CAnimator.h"
#include"CTexture.h"
#include"CObject.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_iCurFrm(1)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
}

void CAnimation::render(HDC _dc)
{
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// 2번째 인자값 좌상단 좌표는 플레이어 중심에 한 프레임의 애니메이션 크기의 절반 만큼 빼서 계산한 값 이다.
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x			   )
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y			   )
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x				)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y				)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x			)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y			)
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
