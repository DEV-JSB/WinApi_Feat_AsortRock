#include "pch.h"
#include "CMissile.h"
#include"CTimeMgr.h"

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.y += 200.f * fDT * m_iDir;

	SetPos(vPos);
}

CMissile::CMissile()
	: m_iDir(1.f)
{
}

CMissile::~CMissile()
{
}
