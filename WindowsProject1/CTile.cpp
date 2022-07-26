#include "pch.h"
#include "CTile.h"

#include"CTexture.h"

CTile::CTile()
	:m_pTileTex(nullptr)
	,m_iIdx(3)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _hdc)
{
	if (nullptr == m_pTileTex)
		return;
	
	// GetTexture Size that I Loaded Tile Set
	UINT iWidt = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	// GetTile Max Col , Row
	UINT iMaxCol = iWidt / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	// 내가 참조할 행 , 열을 알아내는 로직이다.
	UINT iCurRow = (UINT)m_iIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iIdx % iMaxCol;


	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRealPos(GetPos());
	Vec2 vScale = GetScale();


	Rectangle(_hdc, vRenderPos.x, vRenderPos.y, vRenderPos.x + vScale.x, vRenderPos.y + vScale.y);

	BitBlt(_hdc
		, vRenderPos.x
		, vRenderPos.y
		, vScale.x
		, vScale.y
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);

}
