#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
   // float m_iDir; // 위 아래 방향 
    float m_fTheta; // 이동 각도
public:
    void SetDir(float _fTheta)
    {
        m_fTheta = _fTheta;
    }
private:
    virtual void update();
    virtual void render(HDC _hdc);
public:
    CMissile();
    ~CMissile();

};

