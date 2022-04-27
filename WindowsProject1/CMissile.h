#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_iDir; // 위 아래 방향 
public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_iDir = -1.f;
        else
            m_iDir = 1.f;
    }
private:
    virtual void update();
    virtual void render(HDC _hdc);
public:
    CMissile();
    ~CMissile();

};

