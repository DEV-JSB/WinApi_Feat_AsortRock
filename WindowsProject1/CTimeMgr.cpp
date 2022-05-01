#include "pch.h"
#include "CTimeMgr.h"

#include"CCore.h"

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llFrequency{}
	, m_dDT(0.f)
	, m_iCallCount(0)
	, m_dAcc(0.f)
{
		
}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
	// �ʴ� 10000000 fps ����..
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	

	// ���� ī��Ʈ ���� ���� ������ ���� ( ���� ���� ����� ���ؼ� 
	m_llPrevCount = m_llCurCount;
	m_dAcc += m_dDT;

}

void CTimeMgr::render()
{

	++m_iCallCount;

	if (m_dAcc >= 1.f)//????
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.f;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d ,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
