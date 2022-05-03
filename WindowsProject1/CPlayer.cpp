#include "pch.h"
#include "CPlayer.h"
#include"CKeyMgr.h"
#include"CTimeMgr.h"
#include"CSceneMgr.h"
#include"CMissile.h"
#include"CScene.h"
#include"CTexture.h"
#include"CPathMgr.h"

CPlayer::CPlayer()
	:m_pTex(nullptr)
{

	m_pTex = new CTexture;


	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += L"texture\\File.bmp";
	m_pTex->Load(strFilepath);
}
void CPlayer::update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD_CHECK(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD_CHECK(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD_CHECK(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD_CHECK(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}


	if (KEY_TAP_CHECK(KEY::SPACE))
	{
		CreateMissile();
	}
	SetPos(vPos);

}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	//BitBlt(_dc
	//		, (int)(vPos.x - (float)(iWidth / 2))
	//		, (int)(vPos.y - (float)(iHeight / 2))
	//		, iWidth, iHeight
	//		, m_pTex->GetDC()
	//		, 0, 0, SRCCOPY);

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(2, 2, 2));
	// 내가 받은 텍스쳐의 RGB 를 2,2,2 라서 2,2,2 를 무시해라 했더니 잘 된다. ㅋㅋ
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-1.f, -7.f));

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
		delete m_pTex;
}

//void CPlayer::render(HDC _dc)
//{
//}
