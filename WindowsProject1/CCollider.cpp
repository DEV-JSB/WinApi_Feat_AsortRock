#include "pch.h"
#include "CCollider.h"
#include"CObject.h"
#include"CCore.h"

#include"SelectGDI.h"

UINT	CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// 오브젝트의 위치를 따라간다.

	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

}

void CCollider::render(HDC _dc)
{
	//HPEN hGreenPen = CCore::GetInst()->GetPen(PEN_TYPE::GREEN);
	//
	//HPEN hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);
	//
	//HBRUSH hHollowBrush = CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//HBRUSH hDefaultBrush = (HBRUSH)SelectObject(_dc, hHollowBrush);

	SelectGDI p (_dc , PEN_TYPE::BLUE);
	SelectGDI b (_dc, BRUSH_TYPE::HOLLOW);
	// SelectGDI 는 임시 멤버 객체 임으로 
	// 나중에 소멸하니까 소멸자를 무조건 호출하게 되어 있다.

	Rectangle(_dc
		, m_vFinalPos.x - m_vScale.x / 2.f
		, m_vFinalPos.y - m_vScale.y / 2.f
		, m_vFinalPos.x + m_vScale.x / 2.f
		, m_vFinalPos.y + m_vScale.y / 2.f);

	//SelectObject(_dc, hDefaultBrush);
	//SelectObject(_dc, hDefaultPen);
}

void CCollider::OnCollision(CCollider* _pOther)
{

}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
}

