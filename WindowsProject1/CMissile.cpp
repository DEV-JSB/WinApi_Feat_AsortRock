#include "pch.h"
#include "CMissile.h"
#include"CTimeMgr.h"

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.y += 500.f * fDT * m_iDir;

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
	: m_iDir(1.f)
{
}

CMissile::~CMissile()
{
}
