#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;

	LARGE_INTEGER	m_llFrequency; // : 1 초에 얼만큼 값을 세는지 값이 나온다.
	
	double			m_dDT; // 프레임 간의 시간 값
	double			m_dAcc; // 프레임 간의 시간 값 누적시키기
	UINT			m_iCallCount; // 함수 호출 횟수 체크
	UINT			m_iFPS; // 초당 호출 횟수
								   
	// 1. FPS : 1초 동안 몇 프레임을 돌 수 있는지 ( Delta Time )
	// 2. 
public:
	void Init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

