#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_iDir; // �� �Ʒ� ���� 
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
public:
    CMissile();
    ~CMissile();

};

