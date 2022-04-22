#include "CCore.h"
#include"Test.h"
#include"CObject.h"
//#include "CCore.h"
//
//
//CCore* CCore::g_pInst = nullptr;
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CObject g_obj;

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
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

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2,m_ptResolution.y /2 };
	g_obj.m_ptScale = POINT{ 100,100 };


	// 윈도우 식 참
	return S_OK;
}



void CCore::progress()
{

	static int callcount = 0;
	++callcount;

	static int iPrevCount = GetTickCount();

	int CurCount = GetTickCount();

	if (GetTickCount() - iPrevCount > 1000)
	{
		callcount;
		iPrevCount = GetTickCount();
		callcount = 0;
	}

	update();

	render();
}

void CCore::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}




	g_obj.m_ptPos;
}

void CCore::render()
{
	Rectangle(m_hDC, 10, 10, 110, 110);
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x /2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y /2);
}
