#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"
CPathMgr::CPathMgr()
	:m_szContentPath{}
{
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255,m_szContentPath);

	int iLen = wcslen(m_szContentPath);



	wcscat_s(m_szContentPath, 255, L"\\content\\");
	// ->bin\\content\\


	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);


}


CPathMgr::~CPathMgr()
{

}
