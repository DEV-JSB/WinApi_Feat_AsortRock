#pragma once

#include "define.h"

class CCore
{

	SINGLE(CCore);
private:
	HWND	m_hWnd;			//메인 윈도우 핸들
	POINT	m_ptResolution;	//해상도
	HDC		m_hDC; // 메인 윈도우에 Draw 할 DC 
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	void update();
	void render();
private:
	CCore();
	~CCore();
};

