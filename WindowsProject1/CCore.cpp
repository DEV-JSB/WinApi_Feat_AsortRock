#include "CCore.h"
#include"Test.h"

//#include "CCore.h"
//
//
//CCore* CCore::g_pInst = nullptr;
CCore::CCore()
{

}
CCore::~CCore()
{
}


void CCore::progress()
{
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;



	// �ػ󵵿� �°� ������ ũ�� ����

	RECT rt = { 0 , 0 , m_ptResolution.x,m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW , true);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);




	// ������ �� ��
	return S_OK;
}
