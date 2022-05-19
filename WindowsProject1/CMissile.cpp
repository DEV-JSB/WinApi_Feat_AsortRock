#include "pch.h"
#include "CMissile.h"
#include"CTimeMgr.h"
#include"CCollider.h"
void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 100.f * fDT * cosf(m_fTheta);
	//vPos.y -= 100.f * fDT * sinf(m_fTheta);
	vPos.x += 100.f * fDT * m_vDir.x;
	vPos.y += 100.f * fDT * m_vDir.y;
	SetPos(vPos);
}

void CMissile::render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	component_render(_hdc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(1.f, 1.f)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}
