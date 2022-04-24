#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency; // : 1 초에 얼만큼 값을 세는지 값이 나온다.
	// 1. FPS : 1초 동안 몇 프레임을 돌 수 있는지 ( Delta Time )
	// 2. 
public:
	void Init();
};

