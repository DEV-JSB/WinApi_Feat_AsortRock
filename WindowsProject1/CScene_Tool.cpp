#include "pch.h"
#include "CScene_Tool.h"
#include"CKeyMgr.h"
#include"CTile.h"
#include"CCore.h"
#include"CResMgr.h"
CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}
void CScene_Tool::Enter()
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\Tile.bmp");


	// Make Tile
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2(j * TILE_SIZE,i * TILE_SIZE));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	// Camera Look ÁöÁ¤
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CCamera::GetInst()->SetLookAt(Vec2(vResolution/2.f));
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::update()
{
	CScene::update();
	/*if (KEY_TAP_CHECK(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}*/
}

