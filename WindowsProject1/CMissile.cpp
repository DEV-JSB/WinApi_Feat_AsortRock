#include "pch.h"
#include "CMissile.h"
#include"CTimeMgr.h"

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 100.f * fDT * cosf(m_fTheta);
	vPos.y -= 100.f * fDT * sinf(m_fTheta);

	SetPos(vPos);
}

void CMissile::render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}

CMissile::CMissile()
	: m_fTheta(PI/4.f)
{
}

CMissile::~CMissile()
{
}
