#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency; // : 1 �ʿ� ��ŭ ���� ������ ���� ���´�.
	// 1. FPS : 1�� ���� �� �������� �� �� �ִ��� ( Delta Time )
	// 2. 
public:
	void Init();
};

