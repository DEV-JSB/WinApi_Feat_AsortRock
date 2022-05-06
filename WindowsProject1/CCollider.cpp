#include "pch.h"
#include "CCollider.h"
#include"CObject.h"
#include"CCore.h"

#include"SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// ������Ʈ�� ��ġ�� ���󰣴�.

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

	SelectGDI p (_dc , PEN_TYPE::GREEN);
	SelectGDI b (_dc, BRUSH_TYPE::HOLLOW);
	// SelectGDI �� �ӽ� ��� ��ü ������ 
	// ���߿� �Ҹ��ϴϱ� �Ҹ��ڸ� ������ ȣ���ϰ� �Ǿ� �ִ�.

	Rectangle(_dc
		, m_vFinalPos.x - m_vScale.x / 2.f
		, m_vFinalPos.y - m_vScale.y / 2.f
		, m_vFinalPos.x + m_vScale.x / 2.f
		, m_vFinalPos.y + m_vScale.y / 2.f);

	//SelectObject(_dc, hDefaultBrush);
	//SelectObject(_dc, hDefaultPen);
}

