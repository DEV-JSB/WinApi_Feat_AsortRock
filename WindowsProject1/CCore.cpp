#include"pch.h"
#include "CCore.h"
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

	g_obj.SetPos(Vec2((float)m_ptResolution.x/2,(float)m_ptResolution.y /2));
	g_obj.SetScale(Vec2(100,100));


	// 윈도우 식 참
	return S_OK;
}



void CCore::progress()
{

//static int callcount = 0;
//++callcount;
//
//static int iPrevCount = GetTickCount();
//
//int CurCount = GetTickCount();
//
//if (GetTickCount() - iPrevCount > 1000)
//{
//	callcount;
//	iPrevCount = GetTickCount();
//	callcount = 0;
//}

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 0.01;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 0.01;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_hDC, 10, 10, 110, 110);
	Rectangle(m_hDC , (int)vPos.x - vScale.x / 2.f
					, (int)vPos.y - vScale.y / 2.f
					, (int)vPos.x + vScale.x / 2.f
					, (int)vPos.y + vScale.y / 2.f);
}
