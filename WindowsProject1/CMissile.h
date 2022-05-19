#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
   // float m_iDir; // 위 아래 방향 
    float m_fTheta; // 이동 각도


    Vec2  m_vDir;
public:
    void SetDir(float _fTheta)
    {
        m_fTheta = _fTheta;
    }
    void SetDir(Vec2 _vDir) {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
private:
    virtual void update();
    virtual void render(HDC _hdc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
public:
    CMissile();
    ~CMissile();

};

