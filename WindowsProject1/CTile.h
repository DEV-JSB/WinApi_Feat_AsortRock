#pragma once
#include"CObject.h"

class CTexture;

class CTile : public CObject
{
private:
	CTexture* m_pTileTex;
	int m_iIdx;

public :
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTex = _pTex;
	}
public:
	CTile();
	~CTile();
private:
	virtual void update();
	virtual void render(HDC _hdc);


	CLONE(CTile);
};

