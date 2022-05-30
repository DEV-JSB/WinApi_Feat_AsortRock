#pragma once
#include "CObject.h"

class CTexture;


class CPlayer :
    public CObject
{
private:
public:
    virtual void update();
    virtual void render(HDC _dc);

    CPlayer();

    CPlayer(const CPlayer& _origin)
        : CObject(_origin)
    {}

    ~CPlayer();

private:
    void CreateMissile();
    
    CLONE(CPlayer);
};

