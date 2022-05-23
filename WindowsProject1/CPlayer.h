#pragma once
#include "CObject.h"

class CTexture;


class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;
public:
    virtual void update();
    virtual void render(HDC _dc);

    CPlayer();

    CPlayer(const CPlayer& _origin)
        : CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {}

    ~CPlayer();

private:
    void CreateMissile();
    
    CLONE(CPlayer);
};

