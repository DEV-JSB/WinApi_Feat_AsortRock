#include"pch.h"
#include"CKeyMgr.h"
#include "CCore.h"
#include"CObject.h"
#include"CTimeMgr.h"
#include"CSceneMgr.h"
#include"CPathMgr.h"
//#include "CCore.h"
//
//
//CCore* CCore::g_pInst = nullptr;
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}


CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}


int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조절

	RECT rt = { 0 , 0 , m_ptResolution.x,m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW , true);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);


	// 내부적으로 따로 그리기 전용 DC 생성
	m_hDC = GetDC(m_hWnd);


	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	//Manager 초기화
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	



	// 윈도우 식 참
	return S_OK;
}



void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();


	// ==================================
	// Rendering
	// ==================================

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);


	//CTimeMgr::GetInst()->render();
}

