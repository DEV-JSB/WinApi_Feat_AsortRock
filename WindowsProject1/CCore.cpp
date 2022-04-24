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

	// �ػ󵵿� �°� ������ ũ�� ����

	RECT rt = { 0 , 0 , m_ptResolution.x,m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW , true);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);


	// ���������� ���� �׸��� ���� DC ����
	m_hDC = GetDC(m_hWnd);

	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2((float)m_ptResolution.x/2,(float)m_ptResolution.y /2));
	g_obj.SetScale(Vec2(100,100));


	// ������ �� ��
	return S_OK;
}



void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 100.f * DT;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * DT;
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
