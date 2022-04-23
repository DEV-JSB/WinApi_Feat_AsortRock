//#pragma once
//class CCore
//{
//private:
//	static CCore* g_pInst;
//public:
//	static CCore* GetInstance()
//	{
//		// 최초 호출 된 경우 ( static 변수는 반드시 초기화가 한번만 이루어진다 )
//		// 2번 이상 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//		return g_pInst;
//	}
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//private:
//	CCore();
//	~CCore();
//};

#include "define.h"
#include<Windows.h>

class CCore
{

	SINGLE(CCore);
private:
	HWND m_hWnd;			//메인 윈도우 핸들
	POINT m_ptResolution;	//해상도
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	CCore();
	~CCore();
};

