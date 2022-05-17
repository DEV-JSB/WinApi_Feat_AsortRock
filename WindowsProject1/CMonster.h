#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    Vec2 m_vCenterPos;
    float m_fSpeed;
    float m_fMaxDistance;

    int m_iDir; // 1 , -1 

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }

    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }

    void SetCenterPos(Vec2 m_vPos) { m_vCenterPos = m_vPos; }

public:
    virtual void OnCollisionEnter(CCollider* _pOhter);
public:
    virtual void update();
public:
    CMonster();
    ~CMonster();
};

