	#include "pch.h"
#include "CObject.h"
#include"CTimeMgr.h"
#include"CKeyMgr.h"
#include"CCollider.h"

void CObject::update()
{
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	//{
	//	vPos.y -= 200.f * fDT;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	//{
	//	vPos.y += 200.f * fDT;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	//{
	//	vPos.x -= 200.f * fDT;
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	//{
	//	vPos.x += 200.f * fDT;
	//}
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
					(int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));
	component_render(_dc);
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}
}

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_bAllive(true)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete(m_pCollider);
}


void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}