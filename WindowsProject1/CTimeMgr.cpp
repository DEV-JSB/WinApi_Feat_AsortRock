#include "pch.h"
#include "CTimeMgr.h"
CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llFrequency{}
{
		
}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceFrequency(&m_llFrequency);
	// �ʴ� 10000000 fps ����..
}
