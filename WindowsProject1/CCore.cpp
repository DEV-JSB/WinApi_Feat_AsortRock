#include"pch.h"
#include"CKeyMgr.h"
#include "CCore.h"
#include"CObject.h"
#include"CTimeMgr.h"
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

CObject g_obj;

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
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2((float)m_ptResolution.x/2,(float)m_ptResolution.y /2));
	g_obj.SetScale(Vec2(100,100));


	// 윈도우 식 참
	return S_OK;
}



void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT)==KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}
	
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear 화면 재구성

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDC, (int)vPos.x - vScale.x / 2.f
					, (int)vPos.y - vScale.y / 2.f
					, (int)vPos.x + vScale.x / 2.f
					, (int)vPos.y + vScale.y / 2.f);
	Rectangle(m_memDC, (int)vPos.x - vScale.x / 2.f -100
		, (int)vPos.y - vScale.y / 2.f -100
		, (int)vPos.x + vScale.x -100
		, (int)vPos.y + vScale.y-100);

	BitBlt(m_hDC,0,0,m_ptResolution.x,m_ptResolution.y,
			m_memDC, 0, 0,SRCCOPY);
}
