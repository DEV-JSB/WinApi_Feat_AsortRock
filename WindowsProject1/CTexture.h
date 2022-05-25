#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo;

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }
private:
    // 누구나 생성할 수 없게 막자
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;
};

